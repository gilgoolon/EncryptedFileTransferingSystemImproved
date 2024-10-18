#include "SendingAesKeyResponse.hpp"

void protocol::SendingAesKeyResponse::deserialize(const buffer::Buffer& data)
{
	SignupSuccessResponse::deserialize(data);
	m_aes_key = buffer::Buffer(data.begin() + SignupSuccessResponse::size(), data.end());
}

buffer::Buffer protocol::SendingAesKeyResponse::get_aes_key() const
{
	return m_aes_key;
}
