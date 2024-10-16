#pragma once
#include <boost/asio.hpp>

#include "Writer.hpp"

class SocketWriter final : public IWriter {
public:
    explicit SocketWriter(std::shared_ptr<boost::asio::ip::tcp::socket> socket);

    void write(const buffer::Buffer& data) override;

private:
    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};
