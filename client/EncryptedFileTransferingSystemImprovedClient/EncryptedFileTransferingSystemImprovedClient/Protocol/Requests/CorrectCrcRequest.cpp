#include "CorrectCrcRequest.hpp"
#include "../Protocol.hpp"

protocol::CorrectCrcRequest::CorrectCrcRequest(const buffer::Buffer& client_id, const std::string& filename)
    : Request(client_id, protocol::RequestCode::CORRECT_CRC, protocol::FILENAME_SIZE)
    , m_filename(filename)
{
}

buffer::Buffer protocol::CorrectCrcRequest::serialize() const
{
    return concat_vectors(Request::serialize(), buffer::Buffer(m_filename.begin(), m_filename.end()));
}
