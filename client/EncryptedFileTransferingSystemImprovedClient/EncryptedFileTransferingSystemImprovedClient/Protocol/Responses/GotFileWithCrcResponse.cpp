#include "GotFileWithCrcResponse.hpp"
#include "../Protocol.hpp"

void protocol::GotFileWithCrcResponse::deserialize(const buffer::Buffer& data)
{
	SignupSuccessResponse::deserialize(data);
	m_content_size = deserialize_uint32(data.begin() + SignupSuccessResponse::size());
	m_filename = std::string(data.begin() + SignupSuccessResponse::size() + sizeof(m_content_size), data.begin() + SignupSuccessResponse::size() + sizeof(m_content_size) + FILENAME_SIZE);
	m_checksum = deserialize_uint32(data.begin() + SignupSuccessResponse::size() + sizeof(m_content_size) + FILENAME_SIZE);
}

uint32_t protocol::GotFileWithCrcResponse::get_content_size() const
{
	return m_content_size;
}

std::string protocol::GotFileWithCrcResponse::get_filename() const
{
	return m_filename;
}

uint32_t protocol::GotFileWithCrcResponse::get_checksum() const
{
	return m_checksum;
}
