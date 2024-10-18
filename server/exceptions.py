
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


class ClientDoesntExist(Exception):
    """
    When a client tries to log in with a non-existing client id
    """


class ClientAlreadyExists(Exception):
    """
    A client tries to register with a name that already exists
    """


class FileDoesntExistException(Exception):
    """
    When a requested filename doesn't exist in the db or isn't verified
    """
