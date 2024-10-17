import random

from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad


DEFAULT_KEY_SIZE = 8


def decrypt(data: bytes, key: bytes) -> bytes:
    cipher = AES.new(key, AES.MODE_ECB)
    decrypted_data = cipher.decrypt(data)
    return unpad(decrypted_data, AES.block_size)


def generate_key() -> bytes:
    return random.Random().randbytes(DEFAULT_KEY_SIZE)
