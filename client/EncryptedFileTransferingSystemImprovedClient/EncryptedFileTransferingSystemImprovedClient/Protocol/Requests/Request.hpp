#include "../../Common/Buffer.hpp"
#include "Serializable.hpp"

namespace protocol {
	static constexpr uint8_t CLIENT_VERSION = 1;

	enum class RequestCode : uint16_t {
		SIGNUP = 825,
		SEND_PUBLIC_KEY = 826,
		RECONNECT = 827,
		SEND_FILE = 828,
		CORRECT_CRC = 900,
		INCORRECT_CRC_SENDING_AGAIN = 901,
		INCORRECT_CRC_DONE = 902,
	};

	class Request : public ISerializable{
	public:
		explicit Request(const buffer::Buffer& client_id, const RequestCode request_code, const uint32_t payload_size);

		virtual buffer::Buffer serialize() const override;
	private:
		const buffer::Buffer m_client_id;
		const RequestCode m_request_code;
		const uint32_t m_payload_size;
	};
};
