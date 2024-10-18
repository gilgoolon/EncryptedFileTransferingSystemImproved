#include "SocketReader.hpp"


SocketReader::SocketReader(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
    : m_socket(std::move(socket))
{
}

Buffer SocketReader::read(const size_t length)
{
    buffer::Buffer buffer(length);
    boost::asio::read(*m_socket, boost::asio::buffer(buffer, length));
    return buffer;
}
