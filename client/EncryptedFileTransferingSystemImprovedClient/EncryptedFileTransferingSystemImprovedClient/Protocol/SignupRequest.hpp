#include "Request.hpp"

namespace protocol {
	class SignupRequest : public Request {
	public:
		explicit SignupRequest(const buffer::Buffer& client_id, const std::string& client_name);

		virtual buffer::Buffer serialize() const override;

	private:
		const std::string m_client_name;
	};
};
