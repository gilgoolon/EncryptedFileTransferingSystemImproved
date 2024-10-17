import ctypes
import enum
import struct

from protocol.requests import FILENAME_SIZE
from protocol.serializable import ISerializable

VERSION = 3
CLIENT_ID_SIZE = 16


class ResponseCode(enum.Enum):
    SIGNUP_SUCCESS = 1600
    SIGNUP_FAILED = 1601
    SENDING_AES_KEY = 1602
    GOT_FILE_WITH_CRC = 1603
    OK_CONFIRMATION = 1604
    RECONNECT_SUCCESS_SENDING_AES = 1605
    RECONNECT_FAILED = 1606
    SERVER_ERROR = 1607


class Response(ISerializable):
    def __init__(self, code: ResponseCode, payload_size: int) -> None:
        self._code = code
        self._payload_size = payload_size

    def serialize(self) -> bytes:
        packed = struct.pack("<BHI", VERSION, self._code.value, self._payload_size)
        return packed


class SignupSuccessResponse(Response):
    def __init__(self, client_id: bytes) -> None:
        super(SignupSuccessResponse, self).__init__(ResponseCode.SIGNUP_SUCCESS, CLIENT_ID_SIZE)
        self._client_id = client_id

    def serialize(self) -> bytes:
        return super().serialize() + struct.pack(f"<{CLIENT_ID_SIZE}s", self._client_id)


class SignupFailedResponse(Response):
    def __init__(self) -> None:
        super(SignupFailedResponse, self).__init__(ResponseCode.SIGNUP_FAILED, 0)


class SendingAesKeyResponse(Response):
    def __init__(self, client_id: bytes, encrypted_aes_key: bytes) -> None:
        super(SendingAesKeyResponse, self).__init__(ResponseCode.SENDING_AES_KEY,
                                                    CLIENT_ID_SIZE + len(encrypted_aes_key))
        self._client_id = client_id
        self._encrypted_aes_key = encrypted_aes_key

    def serialize(self) -> bytes:
        return super().serialize() + struct.pack(f"<{CLIENT_ID_SIZE}s{len(self._encrypted_aes_key)}s",
                                                 self._client_id, self._encrypted_aes_key)


class GotFileWithCrcResponse(Response):
    def __init__(self, client_id: bytes, content_size: int, filename: str, checksum: int) -> None:
        super(GotFileWithCrcResponse, self).__init__(
            ResponseCode.GOT_FILE_WITH_CRC,
            CLIENT_ID_SIZE + 2 * ctypes.sizeof(ctypes.c_uint32) + FILENAME_SIZE
        )
        self._client_id = client_id
        self._content_size = content_size
        self._filename = filename
        self._checksum = checksum

    def serialize(self) -> bytes:
        return super().serialize() + struct.pack(f"<{CLIENT_ID_SIZE}sI{FILENAME_SIZE}sI",
                                                 self._client_id, self._content_size, self._filename, self._checksum)


class OkConfirmationResponse(Response):
    def __init__(self, client_id: bytes) -> None:
        super(OkConfirmationResponse, self).__init__(ResponseCode.OK_CONFIRMATION, CLIENT_ID_SIZE)
        self._client_id = client_id

    def serialize(self) -> bytes:
        return super().serialize() + struct.pack(f"<{CLIENT_ID_SIZE}s", self._client_id)


class ReconnectSuccessSendingAesResponse(Response):
    def __init__(self, client_id: bytes, encrypted_aes_key: bytes) -> None:
        super(ReconnectSuccessSendingAesResponse, self).__init__(ResponseCode.RECONNECT_SUCCESS_SENDING_AES,
                                                                 CLIENT_ID_SIZE + len(encrypted_aes_key))
        self._client_id = client_id
        self._encrypted_aes_key = encrypted_aes_key

    def serialize(self) -> bytes:
        return super().serialize() + struct.pack(f"<{CLIENT_ID_SIZE}s{len(self._encrypted_aes_key)}s",
                                                 self._client_id, self._encrypted_aes_key)


class ReconnectFailed(Response):
    def __init__(self, client_id: bytes) -> None:
        super(ReconnectFailed, self).__init__(ResponseCode.RECONNECT_FAILED, CLIENT_ID_SIZE)
        self._client_id = client_id

    def serialize(self) -> bytes:
        return super().serialize() + struct.pack(f"<{CLIENT_ID_SIZE}s", self._client_id)
