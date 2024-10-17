#include "Boost.hpp"

using Endpoint = boost::asio::ip::tcp::endpoint;

static boost::asio::io_context g_io_context;

std::shared_ptr<boost_util::Socket> boost_util::connect(const std::string& ip, const uint32_t port)
{
    auto socket = std::make_shared<Socket>(g_io_context);
    socket->connect(Endpoint(boost::asio::ip::address::from_string(ip), port));
    return socket;
}
