#include "ServerCommunicator.hpp"

ServerCommunicator::ServerCommunicator(std::unique_ptr<IReader> server_reader, std::unique_ptr<IWriter> server_writer)
	: m_server_reader(std::move(server_reader))
	, m_server_writer(std::move(server_writer))
{
}
