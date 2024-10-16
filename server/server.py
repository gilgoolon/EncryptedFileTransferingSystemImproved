import socket
import threading


class Server:
    DEFAULT_MAX_BACKLOG = 10

    def __init__(self, port: int, max_backlog: int = DEFAULT_MAX_BACKLOG) -> None:
        self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._server_socket.bind(("0.0.0.0", port))
        self._server_socket.listen(max_backlog)

    def start(self) -> None:
        client_address, client_socket = self._server_socket.accept()
        print(f"Client connected from address: {client_address}")
        threading.Thread(target=self.handle_client, args=(client_socket, )).start()

    def handle_client(self, client_socket: socket.socket) -> None:
        pass
