from pathlib import Path

from db_manager import DBManager
from server import Server

PORT_INFO_PATH = Path("port.info")
DEFAULT_PORT = 1256
DB_PATH = Path("defensive.db")
FILES_PATH = Path("backup")


def main() -> None:
    try:
        port = int(PORT_INFO_PATH.read_text())
    except (ValueError, OSError):
        print(f"WARNING: Defaulted to default port {DEFAULT_PORT}")
        port = DEFAULT_PORT

    db_manager = DBManager(DB_PATH)
    server = Server(db_manager, port, FILES_PATH)
    server.start()


if __name__ == '__main__':
    main()
