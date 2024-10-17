#include "SignupSuccessResponse.hpp"
#include "../Protocol.hpp"

void protocol::SignupSuccessResponse::deserialize(const buffer::Buffer& data)
{
	Response::deserialize(data);
	m_client_id = buffer::Buffer(data.begin() + Response::size(), data.end());
}

buffer::Buffer protocol::SignupSuccessResponse::get_client_id() const
{
	return m_client_id;
}

size_t protocol::SignupSuccessResponse::size() const
{
	return Response::size() + CLIENT_ID_SIZE;
}
