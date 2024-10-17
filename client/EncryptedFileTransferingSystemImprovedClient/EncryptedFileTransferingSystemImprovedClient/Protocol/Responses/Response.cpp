#include <string>
#include <stdexcept>

#include "Response.hpp"

#include "SignupSuccessResponse.hpp"
#include "SignupFailedResponse.hpp"
#include "SendingAesKeyResponse.hpp"
#include "GotFileWithCrcResponse.hpp"
#include "OkConfirmationResponse.hpp"
#include "ReconnectSuccessSendingAesKeyResponse.hpp"
#include "ReconnectFailedResponse.hpp"
#include "ServerErrorResponse.hpp"

void protocol::Response::deserialize(const buffer::Buffer& data)
{
	m_version = deserialize_uint<uint8_t>(data.begin());
	m_response_code = ResponseCode(deserialize_uint<uint16_t>(data.begin() + sizeof m_version));
	m_payload_size = deserialize_uint<uint32_t>(data.begin() + sizeof m_version + sizeof m_response_code);
}

size_t protocol::Response::size() const
{
	return sizeof(m_version) + sizeof(m_response_code) + sizeof(m_payload_size);
}

protocol::ResponseCode protocol::Response::get_response_code() const
{
	return m_response_code;
}

uint32_t protocol::Response::get_payload_size() const
{
	return m_payload_size;
}


std::unique_ptr<protocol::Response> protocol::make_response(const buffer::Buffer& data)
{
	Response header;
	header.deserialize(data);
	std::unique_ptr<Response> response;
	switch (header.get_response_code()) {
	case ResponseCode::SIGNUP_SUCCESS:
		response = std::make_unique<protocol::SignupSuccessResponse>();
		response->deserialize(data);
		return std::move(response);
	case ResponseCode::SIGNUP_FAILED:
		response = std::make_unique<SignupFailedResponse>();
		response->deserialize(data);
		return std::move(response);
	case ResponseCode::SENDING_AES_KEY:
		response = std::make_unique<SendingAesKeyResponse>();
		response->deserialize(data);
		return std::move(response);
	case ResponseCode::GOT_FILE_WITH_CRC:
		response = std::make_unique<GotFileWithCrcResponse>();
		response->deserialize(data);
		return std::move(response);
	case ResponseCode::OK_CONFIRMATION:
		response = std::make_unique<OkConfirmationResponse>();
		response->deserialize(data);
		return std::move(response);
	case ResponseCode::RECONNECT_FAILED:
		response = std::make_unique<ReconnectFailedResponse>();
		response->deserialize(data);
		return std::move(response);
	case ResponseCode::SERVER_ERROR:
		response = std::make_unique<ServerErrorResponse>();
		response->deserialize(data);
		return std::move(response);
	default:
		throw std::invalid_argument("Invalid response code " + std::to_string(static_cast<uint16_t>(header.get_response_code())) + " when parsing a response in protocol::make_response()");
	}
}
