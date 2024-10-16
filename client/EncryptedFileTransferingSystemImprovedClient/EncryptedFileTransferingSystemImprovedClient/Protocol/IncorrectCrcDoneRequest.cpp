#include "IncorrectCrcDoneRequest.hpp"

protocol::IncorrectCrcDoneRequest::IncorrectCrcDoneRequest(const buffer::Buffer& client_id, const std::string& filename)
    : Request(client_id, protocol::RequestCode::INCORRECT_CRC_DONE, filename.size())
    , m_filename(filename)
{
}

buffer::Buffer protocol::IncorrectCrcDoneRequest::serialize() const
{
    return concat_vectors(Request::serialize(), buffer::Buffer(m_filename.begin(), m_filename.end()));
}
