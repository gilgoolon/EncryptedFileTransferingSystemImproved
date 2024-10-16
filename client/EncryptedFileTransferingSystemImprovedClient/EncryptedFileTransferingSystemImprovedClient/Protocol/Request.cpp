
#include "Request.hpp"

protocol::Request::Request(const buffer::Buffer& client_id, const ClientRequestCode request_code, const uint32_t payload_size)
	: m_client_id(client_id)
	, m_request_code(request_code)
	, m_payload_size(payload_size)
{
}

buffer::Buffer protocol::Request::serialize() const
{
	return concat_vectors(m_client_id, serialize_uint8(CLIENT_VERSION), serialize_uint16(static_cast<uint16_t>(m_request_code)), serialize_uint32(m_payload_size));
}

