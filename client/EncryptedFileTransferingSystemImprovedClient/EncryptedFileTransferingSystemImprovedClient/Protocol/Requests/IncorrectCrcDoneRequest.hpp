#pragma once
#include <string>

#include "Request.hpp"

namespace protocol {
	class IncorrectCrcDoneRequest final : public Request {
	public:
		explicit IncorrectCrcDoneRequest(const buffer::Buffer& client_id, const std::string& filename);

		virtual buffer::Buffer serialize() const override;

	private:
		const std::string m_filename;
	};
};
