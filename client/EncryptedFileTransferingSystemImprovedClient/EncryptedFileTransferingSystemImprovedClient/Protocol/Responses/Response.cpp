#include <string>
#include <stdexcept>

#include "Response.hpp"

void protocol::Response::deserialize(const buffer::Buffer& data)
{
	m_version = deserialize_uint<uint8_t>(data.begin());
	m_code = ResponseCode(deserialize_uint<uint16_t>(data.begin() + sizeof m_version));
	m_payload_size = deserialize_uint<uint32_t>(data.begin() + sizeof m_version + sizeof m_code);
}

size_t protocol::Response::size()
{
	return sizeof(m_version) + sizeof(m_code) + sizeof(m_payload_size);
}

protocol::ResponseCode protocol::Response::get_code() const
{
	return m_code;
}

uint32_t protocol::Response::get_payload_size() const
{
	return m_payload_size;
}
