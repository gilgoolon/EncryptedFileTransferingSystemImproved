import sqlite3
import threading
import time
from pathlib import Path
from typing import List

import exceptions
from crypto import aes
from protocol.requests import CLIENT_NAME_SIZE, FILENAME_SIZE
from protocol.responses import CLIENT_ID_SIZE

PUBLIC_KEY_SIZE = 160
PATH_SIZE = FILENAME_SIZE


class DBManager:
    CLIENTS_TABLE_NAME = "clients"
    FILES_TABLE_NAME = "files"

    def __init__(self, path: Path) -> None:
        self._path = path
        self._db_lock = threading.Lock()
        if not self._is_table_exists(self.CLIENTS_TABLE_NAME):
            self._create_clients_table()
        if not self._is_table_exists(self.FILES_TABLE_NAME):
            self._create_files_table()

    def update_client_aes_key(self, client_id: bytes, aes_key: bytes) -> None:
        self._execute_update(f"UPDATE {self.CLIENTS_TABLE_NAME} SET aes_key = ? WHERE id = ?",
                             aes_key, client_id)

    def update_client_public_key(self, client_id: bytes, public_key: bytes) -> None:
        self._execute_update(f"UPDATE {self.CLIENTS_TABLE_NAME} SET public_key = ? WHERE id = ?",
                             public_key, client_id)

    def register_client(self, client_id: bytes, name: str) -> None:
        try:
            self.get_client_id(name)
            raise exceptions.ClientAlreadyExists()
        except exceptions.ClientDoesntExist:
            pass
        self._execute_update(f"INSERT INTO {self.CLIENTS_TABLE_NAME}(id, name) VALUES(?, ?)",
                             client_id, name)

    def get_client_public_key(self, client_id: bytes) -> bytes:
        results = self._execute_select(f"SELECT public_key FROM {self.CLIENTS_TABLE_NAME} WHERE id = ?", client_id)
        if len(results) == 0:
            raise exceptions.ClientDoesntExist()
        return results[0][0]

    def get_client_id(self, name: str) -> bytes:
        results = self._execute_select(f"SELECT id FROM {self.CLIENTS_TABLE_NAME} WHERE name = ?", name)
        if len(results) == 0:
            raise exceptions.ClientDoesntExist()
        return results[0][0]

    def update_client_last_seen(self, client_id: bytes) -> None:
        self._execute_update(f"UPDATE {self.CLIENTS_TABLE_NAME} SET last_seen = ? WHERE id = ?",
                             int(time.time()), client_id)

    def _execute_update(self, sql: str, *args) -> None:
        with sqlite3.connect(self._path) as con:
            cur = con.cursor()
            cur.execute(sql, args)
            con.commit()

    def _execute_script(self, sql: str) -> None:
        with sqlite3.connect(self._path) as con:
            cur = con.cursor()
            cur.executescript(sql)
            con.commit()

    def _execute_select(self, sql: str, *args) -> List:
        with sqlite3.connect(self._path) as con:
            cur = con.cursor()
            cur.execute(sql, args)
            return cur.fetchall()

    def _is_table_exists(self, table_name: str) -> bool:
        return len(self._execute_select("SELECT name FROM sqlite_master "
                                        "WHERE type='table' AND name=?;",
                                        table_name)) > 0

    def _create_clients_table(self) -> None:
        self._execute_script(f"""
        CREATE TABLE {self.CLIENTS_TABLE_NAME} (
        id BLOB({CLIENT_ID_SIZE}) PRIMARY KEY,
        name VARCHAR({CLIENT_NAME_SIZE}) UNIQUE NOT NULL,
        public_key BLOB({PUBLIC_KEY_SIZE}),
        last_seen INTEGER,
        aes_key BLOB({aes.DEFAULT_KEY_SIZE})
        );
        """)

    def _create_files_table(self) -> None:
        self._execute_script(f"""
        CREATE TABLE {self.FILES_TABLE_NAME} (
        client_id BLOB({CLIENT_ID_SIZE}),
        filename VARCHAR({FILENAME_SIZE}),
        path VARCHAR({PATH_SIZE}) PRIMARY KEY,
        verified INTEGER
        );
        """)

    def clean_client(self, name: str) -> None:
        self._execute_update(f"DELETE FROM {self.CLIENTS_TABLE_NAME} WHERE name = ?", name)
