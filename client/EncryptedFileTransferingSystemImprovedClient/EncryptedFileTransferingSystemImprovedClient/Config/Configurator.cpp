#include <sstream>
#include <filesystem>
#include <memory>
using namespace std::filesystem;

#include "Configurator.hpp"
#include "../Common/Writers/SocketWriter.hpp"
#include "../Common/Readers/SocketReader.hpp"
#include "../Common/OsUtils.hpp"
#include "../Common/StringUtils.hpp"
#include "../Common/Boost.hpp"
#include "../Common/Hex.hpp"
#include "../Common/Base64.hpp"
#include "../Client.hpp"

std::unique_ptr<Client> config::make_client(const config::ClientInfo& client_info, const config::TransferInfo& transfer_info)
{
	auto socket = boost_util::connect(transfer_info.server_ip, transfer_info.server_port);
	return std::make_unique<Client>(
		client_info,
		std::make_unique<ServerCommunicator>(
			std::make_unique<SocketReader>(socket),
			std::make_unique<SocketWriter>(socket)
		)
	);
}
