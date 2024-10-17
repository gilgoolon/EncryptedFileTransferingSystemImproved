import random
import socket
from typing import Optional

import exceptions
from crypto import aes, rsa, crc
from protocol.requests import RequestCode, Request, SendPublicKeyPayload, SendFilePayload
from protocol.responses import Response, SignupSuccessResponse, CLIENT_ID_SIZE, SendingAesKeyResponse, \
    ReconnectSuccessSendingAesResponse, GotFileWithCrcResponse


class ClientHandler:
    def __init__(self, client_socket: socket.socket) -> None:
        self._client_socket = client_socket
        self._client_id: Optional[bytes] = None
        self._public_key: Optional[bytes] = None
        self._aes_key: Optional[bytes] = None

    def handle(self) -> None:
        self._handle_connect()
        self._handle_send_file()

    def _handle_connect(self) -> None:
        request = self._receive_request()
        if request.get_code() is RequestCode.SIGNUP:
            self._client_id = random.Random().randbytes(CLIENT_ID_SIZE)
            send_public_key_request = self._send_and_receive(SignupSuccessResponse(self._client_id),
                                                             RequestCode.SEND_PUBLIC_KEY)
            payload = SendPublicKeyPayload(send_public_key_request.get_payload())
            self._public_key = payload.get_public_key()
            self._aes_key = aes.generate_key()
            self._send_response(SendingAesKeyResponse(self._client_id,
                                                      rsa.encrypt(self._aes_key, self._public_key)))

        elif request.get_code() is RequestCode.RECONNECT:
            raise NotImplemented
            public_key = ...  # fetch from db
            self._aes_key = aes.generate_key()
            self._send_response(ReconnectSuccessSendingAesResponse(self._client_id,
                                                                   rsa.encrypt(self._aes_key, public_key)))
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
        request = self._send_and_receive(response)
        if request.get_code() is RequestCode.CORRECT_CRC:
            return file_content
        if request.get_code() is RequestCode.INCORRECT_CRC_DONE:
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
