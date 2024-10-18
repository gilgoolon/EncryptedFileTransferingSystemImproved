import binascii


def calculate(data: bytes) -> int:
    return binascii.crc32(data)
