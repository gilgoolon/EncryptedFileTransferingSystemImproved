
class InvalidStateException(Exception):
    """
    When the server gets a request meant for a different state
    """


class InvalidChecksumException(Exception):
    """
    When a file has a wrong checksum
    """


class InvalidChecksumNoMoreException(Exception):
    """
    When a file has a wrong checksum and not continuing to retry
    """
