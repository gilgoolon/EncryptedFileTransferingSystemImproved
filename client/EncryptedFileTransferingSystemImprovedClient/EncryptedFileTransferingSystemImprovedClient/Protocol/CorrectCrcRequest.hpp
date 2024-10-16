#include <string>

#include "Request.hpp"

namespace protocol {
	class CorrectCrcRequest final : public Request {
	public:
		explicit CorrectCrcRequest(const buffer::Buffer& client_id, const std::string& filename);

		virtual buffer::Buffer serialize() const override;

	private:
		const std::string m_filename;
	};
};
