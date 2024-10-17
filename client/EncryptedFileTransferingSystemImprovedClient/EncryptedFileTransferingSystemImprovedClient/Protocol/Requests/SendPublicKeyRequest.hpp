#pragma once
#include "Request.hpp"

namespace protocol {
	class SendPublicKeyRequest : public Request {
	public:
		explicit SendPublicKeyRequest(const buffer::Buffer& client_id, const std::string& client_name, const buffer::Buffer& public_key);

		virtual buffer::Buffer serialize() const override;

	private:
		const std::string m_client_name;
		const buffer::Buffer m_public_key;
	};
};
