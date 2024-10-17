#pragma once
#include "Response.hpp"

namespace protocol {
	class SignupSuccessResponse : public Response {
	public:
		virtual void deserialize(const buffer::Buffer& data) override;

		buffer::Buffer get_client_id() const;

		size_t size() const;

	private:
		buffer::Buffer m_client_id;
	};
};
