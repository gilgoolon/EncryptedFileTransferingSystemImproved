#include "SendPublicKeyRequest.hpp"

protocol::SendPublicKeyRequest::SendPublicKeyRequest(const buffer::Buffer& client_id, const std::string& client_name, const buffer::Buffer& public_key)
	: Request(client_id, protocol::RequestCode::SEND_PUBLIC_KEY, client_name.size() + m_public_key.size())
	, m_client_name(client_name)
	, m_public_key(public_key)
{
}

buffer::Buffer protocol::SendPublicKeyRequest::serialize() const
{
	return concat_vectors(Request::serialize(), buffer::Buffer(m_client_name.begin(), m_client_name.end()), m_public_key);
}
