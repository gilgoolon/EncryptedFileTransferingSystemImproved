#pragma once
#include <memory>

#include "Common/Readers/Reader.hpp"
#include "Common/Writers/Writer.hpp"

class ServerCommunicator final {
public:
	explicit ServerCommunicator(std::unique_ptr<IReader> server_reader, std::unique_ptr<IWriter> server_writer);

private:
	std::unique_ptr<IReader> m_server_reader;
	std::unique_ptr<IWriter> m_server_writer;
};
