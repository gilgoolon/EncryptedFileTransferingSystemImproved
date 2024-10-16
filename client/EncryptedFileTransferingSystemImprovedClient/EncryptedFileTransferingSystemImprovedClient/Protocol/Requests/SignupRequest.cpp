#include "SignupRequest.hpp"
#include "../Protocol.hpp"
#include "../../Common/StringUtils.hpp"

protocol::SignupRequest::SignupRequest(const std::string& client_name)
	: Request(buffer::Buffer(CLIENT_ID_SIZE, CLIENT_ID_UNINITIALIZED_VALUE), protocol::RequestCode::SIGNUP, CLIENT_NAME_SIZE)
	, m_client_name(client_name)
{
}

buffer::Buffer protocol::SignupRequest::serialize() const
{
	const auto extended_name = string_utils::extend(m_client_name, CLIENT_NAME_SIZE);
	return concat_vectors(Request::serialize(), buffer::Buffer(extended_name.begin(), extended_name.end()));
}
