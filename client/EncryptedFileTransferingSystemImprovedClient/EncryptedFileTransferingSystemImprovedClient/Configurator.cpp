#include <sstream>
#include <filesystem>
using namespace std::filesystem;

#include "Configurator.hpp"
#include "Common/Writers/SocketWriter.hpp"
#include "Common/Readers/SocketReader.hpp"
#include "Common/OsUtils.hpp"
#include "Common/StringUtils.hpp"
#include "Common/Boost.hpp"
#include "Common/Hex.hpp"
#include "Common/Base64.hpp"

static constexpr char ADDRESS_IP_PORT_SEPARATOR = ':';

std::unique_ptr<Client> configurator::make_client(const std::filesystem::path& transfer_info_path, const std::filesystem::path& me_info_path)
{
	std::stringstream transfer_info(os_utils::read_text_file(transfer_info_path));
	std::string line;
	ClientInfo client_info;
	std::getline(transfer_info, line);
	const auto address_tokens = string_utils::split(line, ADDRESS_IP_PORT_SEPARATOR, string_utils::SPLIT_ONCE);
	const std::string server_ip = address_tokens.at(0);
	const uint32_t server_port = std::stoi(address_tokens.at(1));
	std::getline(transfer_info, client_info.name);
	std::getline(transfer_info, line);
	const std::filesystem::path file_to_transfer = line;

	if (std::filesystem::exists(me_info_path)) {
		client_info = configurator::make_client_info(me_info_path);
	}

	auto socket = connect(server_ip, server_port);

	return std::make_unique<Client>(
		client_info,
		std::make_unique<ServerCommunicator>(
			std::make_unique<SocketReader>(socket),
			std::make_unique<SocketWriter>(socket)
		),
		file_to_transfer
	);
}

ClientInfo configurator::make_client_info(const std::filesystem::path& me_info_path)
{
	std::stringstream me_info(os_utils::read_text_file(me_info_path));
	std::string line;

	std::getline(me_info, line);
	const std::string name = line;

	std::getline(me_info, line);
	const buffer::Buffer id = hex::decode(line);

	std::getline(me_info, line);
	const buffer::Buffer private_key = base64::decode(line);

	return ClientInfo{ name, id, private_key };
}
