#include "SignupRequest.hpp"
#include "../Protocol.hpp"
#include "../../Common/StringUtils.hpp"

protocol::SignupRequest::SignupRequest(const buffer::Buffer& client_id, const std::string& client_name)
	: Request(client_id, protocol::RequestCode::SIGNUP, client_name.size())
	, m_client_name(client_name)
{
}

buffer::Buffer protocol::SignupRequest::serialize() const
{
	const auto extended_name = string_utils::extend(m_client_name, CLIENT_NAME_SIZE);
	return concat_vectors(Request::serialize(), buffer::Buffer(extended_name.begin(), extended_name.end()));
}
