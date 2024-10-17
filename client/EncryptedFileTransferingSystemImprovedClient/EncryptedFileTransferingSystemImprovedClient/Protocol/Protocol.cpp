#include "Protocol.hpp"

#include "Responses/SignupSuccessResponse.hpp"
#include "Responses/SignupFailedResponse.hpp"
#include "Responses/SendingAesKeyResponse.hpp"
#include "Responses/GotFileWithCrcResponse.hpp"
#include "Responses/OkConfirmationResponse.hpp"
#include "Responses/ReconnectSuccessSendingAesKeyResponse.hpp"
#include "Responses/ReconnectFailedResponse.hpp"
#include "Responses/ServerErrorResponse.hpp"

std::unique_ptr<protocol::Response> protocol::make_response(const buffer::Buffer& data)
{
	Response header;
	header.deserialize(data);
	std::unique_ptr<Response> response;
	switch (header.get_code()) {
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
		throw std::invalid_argument("invalid response code " + std::to_string(static_cast<uint16_t>(header.get_code())) + " when parsing a response in protocol::make_response()");
	}
}