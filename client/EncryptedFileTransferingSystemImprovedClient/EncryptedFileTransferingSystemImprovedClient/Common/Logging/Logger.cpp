#include "Logger.hpp"

static const std::unordered_map<logging::LogLevel, std::string> log_level_to_string = {
    { logging::LogLevel::INFO, "INFO" },
    { logging::LogLevel::WARNING, "WARNING" },
    { logging::LogLevel::ERROR, "ERROR" }
};

logging::Logger::Logger()
    : m_log_mutex(std::make_shared<std::mutex>())
{
}

void logging::Logger::log(const LogLevel level, const std::string& message)
{
    autos::AutoLock logging_lock(m_log_mutex);

    std::string level_str = log_level_to_string.at(level);

    std::cout << "[" << level_str << "] " << message << std::endl;
}

logging::Logger& logging::get_logger()
{
    static Logger instance;
    return instance;
}
