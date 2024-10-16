#pragma once
#include <boost/asio.hpp>

#include "Reader.hpp"
using buffer::Buffer;

class SocketReader final : public IReader {
public:
    SocketReader(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

    Buffer read(const size_t length) override;

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};
