
#include "Request.hpp"

protocol::Request::Request(const buffer::Buffer& client_id, const RequestCode request_code, const uint32_t payload_size)
	: m_client_id(client_id)
	, m_request_code(request_code)
	, m_payload_size(payload_size)
{
}

buffer::Buffer protocol::Request::serialize() const
{
	return concat_vectors(m_client_id, serialize_uint<uint8_t>(CLIENT_VERSION), serialize_uint<uint16_t>(static_cast<uint16_t>(m_request_code)), serialize_uint<uint32_t>(m_payload_size));
}

