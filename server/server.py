import logging
import socket
import threading

from client_handler import ClientHandler
from db.db_manager import DBManager
from protocol.responses import Response, ResponseCode


class Server:
    DEFAULT_MAX_BACKLOG = 10

    def __init__(self, db_manager: DBManager, port: int, max_backlog: int = DEFAULT_MAX_BACKLOG) -> None:
        self._db_manager = db_manager
        self._server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._server_socket.bind(("0.0.0.0", port))
        self._server_socket.listen(max_backlog)

    def start(self) -> None:
        while True:
            client_socket, client_address = self._server_socket.accept()
            print(f"Client connected from: {client_address}")
            threading.Thread(target=self.handle_client, args=(client_socket, )).start()

    def handle_client(self, client_socket: socket.socket) -> None:
        try:
            handler = ClientHandler(client_socket, self._db_manager)
            handler.handle()
        except Exception as e:
            client_socket.send(Response(ResponseCode.SERVER_ERROR, 0).serialize())
            logging.exception(e)
            print(f"Server error when handling client: {e}")
