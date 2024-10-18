#include <sstream>

#include "ClientInfo.hpp"
#include "../Common/Hex.hpp"
#include "../Common/Base64.hpp"
#include "../Common/OsUtils.hpp"

std::string config::ClientInfo::serialize() const
{
	std::ostringstream oss;
	oss << name << std::endl << hex::encode(id) << std::endl << base64::encode(private_key) << std::endl;
	return oss.str();
}

config::ClientInfo config::make_client_info(const std::filesystem::path& me_info_path)
{
	std::stringstream me_info(os_utils::read_text_file(me_info_path));
	std::string line;

	std::getline(me_info, line);
	const std::string name = line;

	std::getline(me_info, line);
	const buffer::Buffer id = hex::decode(line);

	std::getline(me_info, line);
	const buffer::Buffer private_key = base64::decode(line);

	return ClientInfo{ name, id, private_key, true };
}
