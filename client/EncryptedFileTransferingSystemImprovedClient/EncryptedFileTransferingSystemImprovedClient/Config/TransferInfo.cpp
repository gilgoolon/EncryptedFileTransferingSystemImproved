#include <string>
#include <sstream>

#include "TransferInfo.hpp"
#include "../Common/OsUtils.hpp"
#include "../Common/StringUtils.hpp"

static constexpr char ADDRESS_IP_PORT_SEPARATOR = ':';

config::TransferInfo config::make_transfer_info(const std::filesystem::path& transfer_info_path)
{
	TransferInfo result;
	std::stringstream transfer_info(os_utils::read_text_file(transfer_info_path));
	std::string line;
	std::getline(transfer_info, result.server_ip, ADDRESS_IP_PORT_SEPARATOR);
	std::getline(transfer_info, line);
	result.server_port = std::stoi(line);
	std::getline(transfer_info, result.client_name);
	std::getline(transfer_info, line);
	result.file_to_transfer = line;
    return result;
}
