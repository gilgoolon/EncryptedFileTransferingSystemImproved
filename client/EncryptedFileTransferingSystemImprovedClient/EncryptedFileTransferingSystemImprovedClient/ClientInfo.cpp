#include <sstream>

#include "ClientInfo.hpp"
#include "Common/Hex.hpp"
#include "Common/Base64.hpp"

std::string ClientInfo::serialize() const
{
	std::ostringstream oss;
	oss << name << std::endl << hex::encode(id) << std::endl << base64::encode(private_key) << std::endl;
	return oss.str();
}
