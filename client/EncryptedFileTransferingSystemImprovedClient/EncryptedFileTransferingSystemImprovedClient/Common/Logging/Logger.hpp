#pragma once
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>

#include "../Autos/AutoLock.hpp"

#define LOG(level_, message_) logging::get_logger().log(level_, message_);
#define LOG_INFO(message_) LOG(logging::LogLevel::INFO_, message_)
#define LOG_WARNING(message_) LOG(logging::LogLevel::WARNING_, message_)
#define LOG_ERROR(message_) LOG(logging::LogLevel::ERROR_, message_)

namespace logging {

    enum class LogLevel {
        INFO_,
        WARNING_,
        ERROR_
    };

    class Logger final {
    public:
        void log(const LogLevel level, const std::string& message);

    private:
        std::shared_ptr<std::mutex> m_log_mutex;

        explicit Logger();
        ~Logger() = default;

        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger& operator=(Logger*&) = delete;

        friend Logger& get_logger();
    };

    Logger& get_logger();
};
