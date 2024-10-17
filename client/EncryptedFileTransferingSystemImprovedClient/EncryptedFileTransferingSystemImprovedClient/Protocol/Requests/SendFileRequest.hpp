#include "Request.hpp"

namespace protocol {
	class SendFileRequest final : public Request {
	public:
		explicit SendFileRequest(const buffer::Buffer& client_id, const buffer::Buffer& content, const uint32_t original_size, const std::string& filename);

		virtual buffer::Buffer serialize() const override;

	private:
		const buffer::Buffer m_content;
		const uint32_t m_original_size;
		const std::string m_filename;
	};
};
