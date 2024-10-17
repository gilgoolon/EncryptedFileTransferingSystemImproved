import abc


class ISerializable(abc.ABC):
    @abc.abstractmethod
    def serialize(self) -> bytes:
        pass
