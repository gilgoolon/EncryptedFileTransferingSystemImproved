#include "CorrectCrcRequest.hpp"

protocol::CorrectCrcRequest::CorrectCrcRequest(const buffer::Buffer& client_id, const std::string& filename)
    : Request(client_id, protocol::RequestCode::CORRECT_CRC, filename.size())
    , m_filename(filename)
{
}

buffer::Buffer protocol::CorrectCrcRequest::serialize() const
{
    return concat_vectors(Request::serialize(), buffer::Buffer(m_filename.begin(), m_filename.end()));
}
