#pragma once
#include "SignupSuccessResponse.hpp"

namespace protocol {
	class SendingAesKeyResponse final : public SignupSuccessResponse {
	public:
		virtual void deserialize(const buffer::Buffer& data) override;

		buffer::Buffer get_aes_key() const;

	private:
		buffer::Buffer m_aes_key;
	};
};
