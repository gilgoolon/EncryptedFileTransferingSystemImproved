#include <string>
#include <filesystem>


namespace config {
	struct TransferInfo {
		std::string server_ip;
		uint32_t server_port;
		std::string client_name;
		std::filesystem::path file_to_transfer;
	};

	TransferInfo make_transfer_info(const std::filesystem::path& tansfer_info_path);
};
