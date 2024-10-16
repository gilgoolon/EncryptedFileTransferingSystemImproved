#include "SignupRequest.hpp"

protocol::SignupRequest::SignupRequest(const buffer::Buffer& client_id, const std::string& client_name)
	: Request(client_id, protocol::RequestCode::SIGNUP, client_name.size())
	, m_client_name(client_name)
{
}

buffer::Buffer protocol::SignupRequest::serialize() const
{
	return concat_vectors(Request::serialize(), buffer::Buffer(m_client_name.begin(), m_client_name.end()));
}
