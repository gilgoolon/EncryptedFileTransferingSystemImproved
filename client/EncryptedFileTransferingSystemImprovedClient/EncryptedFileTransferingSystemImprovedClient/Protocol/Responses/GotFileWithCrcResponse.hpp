#pragma once
#include "SignupSuccessResponse.hpp"

namespace protocol {
	static constexpr size_t FILENAME_SIZE = 255;

	class GotFileWithCrcResponse final : public SignupSuccessResponse {
	public:
		virtual void deserialize(const buffer::Buffer& data) override;

		uint32_t get_content_size() const;

		std::string get_filename() const;

		uint32_t get_checksum() const;

	private:
		uint32_t m_content_size;
		std::string m_filename;
		uint32_t m_checksum;
	};
};
