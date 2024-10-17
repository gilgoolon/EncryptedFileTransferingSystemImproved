#include <string>

#include "Request.hpp"

namespace protocol {
	class IncorrectCrcSendingAgainRequest final : public Request {
	public:
		explicit IncorrectCrcSendingAgainRequest(const buffer::Buffer& client_id, const std::string& filename);

		virtual buffer::Buffer serialize() const override;

	private:
		const std::string m_filename;
	};
};
