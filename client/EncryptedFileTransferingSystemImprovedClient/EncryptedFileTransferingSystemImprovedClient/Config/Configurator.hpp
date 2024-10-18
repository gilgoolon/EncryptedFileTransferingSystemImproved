#pragma once
#include <filesystem>

#include "TransferInfo.hpp"
#include "ClientInfo.hpp"
#include "../Client.hpp"

namespace config {
	std::unique_ptr<Client> make_client(const config::ClientInfo& client_info, const TransferInfo& transfer_info);
};