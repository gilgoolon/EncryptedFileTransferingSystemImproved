#pragma once
#include <memory>

#include "Common/Readers/Reader.hpp"
#include "Common/Writers/Writer.hpp"
#include "Protocol/Requests/Request.hpp"
#include "Protocol/Responses/Response.hpp"

class ServerCommunicator final {
public:
	explicit ServerCommunicator(std::unique_ptr<IReader> server_reader, std::unique_ptr<IWriter> server_writer);

	void send(std::unique_ptr<protocol::Request> request);

	std::unique_ptr<protocol::Response> receive();

	std::unique_ptr<protocol::Response> send_and_receive(std::unique_ptr<protocol::Request> request);

	std::unique_ptr<protocol::Response> send_and_receive(std::unique_ptr<protocol::Request> request, const protocol::ResponseCode expected_response);

private:
	std::unique_ptr<IReader> m_server_reader;
	std::unique_ptr<IWriter> m_server_writer;
};
