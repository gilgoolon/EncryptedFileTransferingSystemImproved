#include "SendPublicKeyRequest.hpp"
#include "../Protocol.hpp"
#include "../../Common/StringUtils.hpp"

protocol::SendPublicKeyRequest::SendPublicKeyRequest(const buffer::Buffer& client_id, const std::string& client_name, const buffer::Buffer& public_key)
	: Request(client_id, protocol::RequestCode::SEND_PUBLIC_KEY, client_name.size() + m_public_key.size())
	, m_client_name(client_name)
	, m_public_key(public_key)
{
}

buffer::Buffer protocol::SendPublicKeyRequest::serialize() const
{
	const auto extended_name = string_utils::extend(m_client_name, CLIENT_NAME_SIZE);
	return concat_vectors(Request::serialize(), buffer::Buffer(extended_name.begin(), extended_name.end()), m_public_key);
}
