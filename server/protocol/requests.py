import ctypes
import enum
import struct

CLIENT_NAME_SIZE = 255
FILENAME_SIZE = 255


class RequestCode(enum.Enum):
    SIGNUP = 825
    SEND_PUBLIC_KEY = 826
    RECONNECT = 827
    SEND_FILE = 828
    CORRECT_CRC = 900
    INCORRECT_CRC_SENDING_AGAIN = 901
    INCORRECT_CRC_DONE = 902


class Request:
    def __init__(self, data: bytes) -> None:
        self._version, self._code, self._payload_size = struct.unpack("<BHI", data[:self.size()])
        self._code = RequestCode(self._code)
        self._payload = data[self.size():]

    def get_code(self) -> RequestCode:
        return self._code

    def get_payload_size(self) -> int:
        return self._payload_size

    @classmethod
    def size(cls) -> int:
        return ctypes.sizeof(ctypes.c_uint8) + ctypes.sizeof(ctypes.c_uint16) + ctypes.sizeof(ctypes.c_uint32)

    def get_payload(self):
        return self._payload


class SignupPayload:
    def __init__(self, data: bytes) -> None:
        self._client_name: str = data.decode().split('\0', 1)[0]

    def get_client_name(self) -> str:
        return self._client_name

    @classmethod
    def size(cls) -> int:
        return CLIENT_NAME_SIZE


class SendPublicKeyPayload(SignupPayload):
    def __init__(self, data: bytes) -> None:
        super(SendPublicKeyPayload, self).__init__(data[:super().size()])
        self._public_key = data[super().size():]

    def get_public_key(self) -> bytes:
        return self._public_key


ReconnectPayload = SignupPayload


class SendFilePayload:
    def __init__(self, data: bytes) -> None:
        self._content_size, self._original_file_size, self._packet_number, self._total_packets, self._filename \
            = struct.unpack(f"<IIHH{FILENAME_SIZE}s", data[:ctypes.sizeof(ctypes.c_uint32) * 2 +
                                                           ctypes.sizeof(ctypes.c_uint16) * 2 + FILENAME_SIZE])
        self._content = data[ctypes.sizeof(ctypes.c_uint32) * 2 + ctypes.sizeof(ctypes.c_uint16) * 2
                             + FILENAME_SIZE:]
        self._filename = self._filename.decode().split('\0', 1)[0]

    def get_content_size(self) -> int:
        return self._content_size

    def get_original_file_size(self) -> int:
        return self._original_file_size

    def get_packet_number(self) -> int:
        return self._packet_number

    def get_total_packets(self) -> int:
        return self._total_packets

    def get_filename(self) -> str:
        return self._filename

    def get_content(self) -> bytes:
        return self._content


class CorrectCrcPayload:
    def __init__(self, data: bytes) -> None:
        self._filename = data.decode().split('\0', 1)[0]

    def get_filename(self) -> str:
        return self._filename


IncorrectCrcSendingAgainPayload = CorrectCrcPayload
IncorrectCrcDonePayload = CorrectCrcPayload
