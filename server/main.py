from pathlib import Path

from server import Server

PORT_INFO_PATH = Path("port.info")
DEFAULT_PORT = 1256


def main() -> None:
    try:
        port = int(PORT_INFO_PATH.read_text())
    except (ValueError, OSError):
        print(f"WARNING: Defaulted to default port {DEFAULT_PORT}")
        port = DEFAULT_PORT

    server = Server(port)
    server.start()


if __name__ == '__main__':
    main()
