#pragma once
#include <memory>
#include <unordered_map>
#include <stdexcept>

#include "Deserializable.hpp"

namespace protocol {
	
#define DEFINE_RESPONSE_CODES \
ENUM_CODE(SIGNUP_SUCCESS, 1600) \
ENUM_CODE(SIGNUP_FAILED, 1601) \
ENUM_CODE(SENDING_AES_KEY, 1602) \
ENUM_CODE(GOT_FILE_WITH_CRC, 1603) \
ENUM_CODE(OK_CONFIRMATION, 1604) \
ENUM_CODE(RECONNECT_SUCCESS_SENDING_AES, 1605) \
ENUM_CODE(RECONNECT_FAILED, 1606) \
ENUM_CODE(SERVER_ERROR, 1607) \

#define ENUM_CODE(code, value) code = value,

enum class ResponseCode : uint16_t {
	DEFINE_RESPONSE_CODES
};

#undef ENUM_CODE

#define ENUM_CODE(code, _) \
case ResponseCode::code: \
    return #code;

inline std::string to_string(ResponseCode code)
{
	switch (code) {
		DEFINE_RESPONSE_CODES
	default:
		throw std::invalid_argument(std::string("invalid ResponseCode value ") + std::to_string(static_cast<uint32_t>(code)) + " passed to to_string(ResponseCode)");
	}
}

class Response : public IDeserializable {
public:
	virtual void deserialize(const buffer::Buffer& data) override;

	static size_t size();

	ResponseCode get_code() const;

	uint32_t get_payload_size() const;

private:
	uint8_t m_version;
	ResponseCode m_code;
	uint32_t m_payload_size;
};
};
