#include "SendFileRequest.hpp"
#include "../Protocol.hpp"
#include "../../Common/StringUtils.hpp"

protocol::SendFileRequest::SendFileRequest(const buffer::Buffer& client_id, const buffer::Buffer& content, const uint32_t original_size, const std::string& filename)
	: Request(client_id, protocol::RequestCode::SEND_FILE, sizeof(uint32_t) + sizeof(original_size) + sizeof(uint16_t) + sizeof(uint16_t) + filename.size() + content.size())
	, m_content(content)
	, m_original_size(original_size)
	, m_filename(filename)
{
}

buffer::Buffer protocol::SendFileRequest::serialize() const
{
	static constexpr size_t TOTAL_PACKETS = 1, PACKET_NUMBER = 1;
	const std::string extended_filename = string_utils::extend(m_filename, FILENAME_SIZE);
	return concat_vectors(
		Request::serialize(),
		serialize_uint32(m_content.size()),
		serialize_uint32(m_original_size),
		serialize_uint16(PACKET_NUMBER),
		serialize_uint16(TOTAL_PACKETS),
		buffer::Buffer(extended_filename.begin(), extended_filename.end()),
		m_content
	);
}
