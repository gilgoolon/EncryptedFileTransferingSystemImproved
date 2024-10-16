#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>

namespace boost_util {
	using Socket = boost::asio::ip::tcp::socket;

	std::shared_ptr<Socket> connect(const std::string& ip, const uint32_t port);
};
