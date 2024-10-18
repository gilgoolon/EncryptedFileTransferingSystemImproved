import logging
import random
import socket
from typing import Optional

import exceptions
from crypto import aes, rsa, crc
from db.db_manager import DBManager
from protocol.requests import RequestCode, Request, SendPublicKeyPayload, SendFilePayload, ReconnectPayload, \
    SignupPayload
from protocol.responses import Response, SignupSuccessResponse, CLIENT_ID_SIZE, SendingAesKeyResponse, \
    ReconnectSuccessSendingAesResponse, GotFileWithCrcResponse, OkConfirmationResponse, ReconnectFailedResponse, \
    SignupFailedResponse


class ClientHandler:
    def __init__(self, client_socket: socket.socket, db_manager: DBManager) -> None:
        self._client_socket = client_socket
        self._db_manager = db_manager
        self._client_name: Optional[str] = None
        self._client_id: Optional[bytes] = None
        self._public_key: Optional[bytes] = None
        self._aes_key: Optional[bytes] = None

    def handle(self) -> None:
        try:
            self._handle_connect()
        except exceptions.ClientDoesntExist:
            self._send_response(ReconnectFailedResponse(bytes([0] * CLIENT_ID_SIZE)))
            self._db_manager.clean_client(self._client_name)
            return
        except exceptions.ClientAlreadyExists:
            self._send_response(SignupFailedResponse())
            return
        self._handle_send_file()

    def _handle_connect(self) -> None:
        request = self._receive_request()
        if request.get_code() is RequestCode.SIGNUP:
            self._client_name = SignupPayload(request.get_payload()).get_client_name()
            self._client_id = random.Random().randbytes(CLIENT_ID_SIZE)
            self._db_manager.register_client(self._client_id, self._client_name)
            self._db_manager.update_client_last_seen(self._client_id)
            send_public_key_request = self._send_and_receive(SignupSuccessResponse(self._client_id),
                                                             RequestCode.SEND_PUBLIC_KEY)
            self._db_manager.update_client_last_seen(self._client_id)
            self._public_key = SendPublicKeyPayload(send_public_key_request.get_payload()).get_public_key()
            self._db_manager.update_client_public_key(self._client_id, self._public_key)
            self._aes_key = aes.generate_key()
            self._db_manager.update_client_aes_key(self._client_id, self._aes_key)
            self._send_response(SendingAesKeyResponse(self._client_id,
                                                      rsa.encrypt(self._aes_key, self._public_key)))

        elif request.get_code() is RequestCode.RECONNECT:
            self._client_name = ReconnectPayload(request.get_payload()).get_client_name()
            self._client_id = self._db_manager.get_client_id(self._client_name)
            self._db_manager.update_client_last_seen(self._client_id)
            self._public_key = self._db_manager.get_client_public_key(self._client_id)
            self._aes_key = aes.generate_key()
            self._db_manager.update_client_aes_key(self._client_id, self._aes_key)
            self._send_response(ReconnectSuccessSendingAesResponse(self._client_id,
                                                                   rsa.encrypt(self._aes_key, self._public_key)))
        else:
            raise exceptions.InvalidStateException(f"Expected a reconnect or signup request when connecting, "
                                                   f"got {request.get_code()}")

    def _handle_send_file(self) -> None:
        content = bytes()
        while True:
            try:
                content = self._try_receive_file()
                break
            except exceptions.InvalidChecksumException:
                continue
        # save file in db
        print(f"Saving file in db... Size: {len(content)} bytes")

    def _try_receive_file(self) -> Optional[bytes]:
        request = self._receive_request(RequestCode.SEND_FILE)
        send_file_payload = SendFilePayload(request.get_payload())
        file_content = aes.decrypt(send_file_payload.get_content(),
                                   self._aes_key)
        checksum = crc.calculate(file_content)
        response = GotFileWithCrcResponse(self._client_id, len(send_file_payload.get_content()),
                                          send_file_payload.get_filename(), checksum)
        confirmation_request = self._send_and_receive(response)
        if confirmation_request.get_code() is RequestCode.CORRECT_CRC:
            self._send_response(OkConfirmationResponse(self._client_id))
            return file_content
        if confirmation_request.get_code() is RequestCode.INCORRECT_CRC_DONE:
            raise exceptions.InvalidChecksumNoMoreException("Got invalid checksum and client is done sending")
        raise exceptions.InvalidChecksumException()

    def _receive_request(self, expected_request: Optional[RequestCode] = None) -> Request:
        header_data = self._client_socket.recv(Request.size())
        request = Request(header_data + self._client_socket.recv(Request(header_data).get_payload_size()))
        if expected_request is not None and request.get_code() is not expected_request:
            raise exceptions.InvalidStateException(
                f"Expected {expected_request.name} request, actual was {request.get_code().name}")
        return request

    def _send_response(self, response: Response) -> None:
        serialized = response.serialize()
        self._client_socket.send(serialized)

    def _send_and_receive(self, response: Response, expected_code: Optional[RequestCode] = None) -> Request:
        self._send_response(response)
        return self._receive_request(expected_request=expected_code)
