
class InvalidStateException(Exception):
    """
    When the server gets a request meant for a different state
    """
