#pragma once
#include <memory>

#include "Deserializable.hpp"

namespace protocol {
	enum class ResponseCode : uint16_t {
		SIGNUP_SUCCESS = 1600,
		SIGNUP_FAILED = 1601,
		SENDING_AES_KEY = 1602,
		GOT_FILE_WITH_CRC = 1603,
		OK_CONFIRMATION = 1604,
		RECONNECT_SUCCESS_SENDING_AES = 1605,
		RECONNECT_FAILED = 1606,
		SERVER_ERROR = 1607,
	};

	class Response : public IDeserializable {
	public:
		virtual void deserialize(const buffer::Buffer& data) override;

		static size_t size();

		ResponseCode get_response_code() const;

		uint32_t get_payload_size() const;

	private:
		uint8_t m_version;
		ResponseCode m_response_code;
		uint32_t m_payload_size;
	};

	std::unique_ptr<Response> make_response(const buffer::Buffer& data);
};
