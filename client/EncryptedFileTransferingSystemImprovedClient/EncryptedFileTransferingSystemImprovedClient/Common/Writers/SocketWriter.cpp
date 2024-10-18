#include "SocketWriter.hpp"

using buffer::Buffer;

SocketWriter::SocketWriter(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : m_socket(std::move(socket))
{
}

void SocketWriter::write(const buffer::Buffer& data)
{
    boost::asio::write(*m_socket, boost::asio::buffer(data));
}
