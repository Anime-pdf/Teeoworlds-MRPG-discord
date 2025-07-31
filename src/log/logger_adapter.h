#ifndef LOG_LOGGER_ADAPTER_H
#define LOG_LOGGER_ADAPTER_H

#include <functional>

#include <crow/logging.h>
#include <dpp/dispatcher.h>

#include "logger.h"

class CrowLogAdapter : public crow::ILogHandler {
public:
    CrowLogAdapter() = default;
    void log(std::string message, crow::LogLevel level) override {
        g_Logger.Log(AdaptCrowLogLevel(level), "{}", message);
    }
};

class DppLogAdapter
{
public:
    static std::function<void(const dpp::log_t &Log)> Logger()
    {
        return [](const dpp::log_t& event) {
            g_Logger.Log(AdaptDppLogLevel(event.severity), "{}", event.message);
        };
    }
};

#endif // LOG_LOGGER_ADAPTER_H
