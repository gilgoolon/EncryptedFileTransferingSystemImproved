#pragma once
#include <string>

#include "Request.hpp"

namespace protocol {
	class ReconnectRequest final : public Request {
	public:
		explicit ReconnectRequest(const buffer::Buffer& client_id, const std::string& client_name);

		virtual buffer::Buffer serialize() const override;

	private:
		const std::string m_client_name;
	};
};
