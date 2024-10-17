#include "ServerCommunicator.hpp"
#include "Protocol/Protocol.hpp"

ServerCommunicator::ServerCommunicator(std::unique_ptr<IReader> server_reader, std::unique_ptr<IWriter> server_writer)
	: m_server_reader(std::move(server_reader))
	, m_server_writer(std::move(server_writer))
{
}

void ServerCommunicator::send(std::unique_ptr<protocol::Request> request)
{
	m_server_writer->write(request->serialize());
}

std::unique_ptr<protocol::Response> ServerCommunicator::receive()
{
	const auto header_buffer = m_server_reader->read(protocol::Response::size());
	protocol::Response header;
	header.deserialize(header_buffer);
	const auto payload_buffer = m_server_reader->read(header.get_payload_size());
	return protocol::make_response(concat_vectors(header_buffer, payload_buffer));
}

std::unique_ptr<protocol::Response> ServerCommunicator::send_and_receive(std::unique_ptr<protocol::Request> request)
{
	send(std::move(request));
	return std::move(receive());
}

std::unique_ptr<protocol::Response> ServerCommunicator::send_and_receive(std::unique_ptr<protocol::Request> request, const protocol::ResponseCode expected_response)
{
	send(std::move(request));
	auto response = receive();
	if (response->get_code() != expected_response) {
		throw std::runtime_error("unexpected response. expected code " + protocol::to_string(expected_response) + ", actual was " + protocol::to_string(response->get_code()));
	}
	return std::move(response);
}

