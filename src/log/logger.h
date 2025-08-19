#ifndef LOG_LOGGER_H
#define LOG_LOGGER_H

#include <format>

#include <dpp/misc-enum.h>
#include <crow/logging.h>

#include <utility/utils.h>

enum class LogLevel
{
    Trace = 0,
    Debug,
    Info,
    Warning,
    Error,
    Critical,
};

LogLevel AdaptDppLogLevel(dpp::loglevel Level);
LogLevel AdaptCrowLogLevel(crow::LogLevel Level);

const char *LogLevelStr(LogLevel Level);
const char *LogLevelColor(LogLevel Level);

class Logger
{
    LogLevel m_Level = LogLevel::Info;

public:
    void SetLogLevel(LogLevel Level)
    {
        m_Level = Level;
    }

    template<typename... TArgs>
    void Log(LogLevel Level, std::format_string<TArgs...> Fmt, TArgs&&... Args)
    {
        if(Level < m_Level)
            return;
        std::cout << std::format("{}[{}] {}: {}", LogLevelColor(Level), current_date_time(), LogLevelStr(Level), std::format(Fmt, std::forward<TArgs>(Args)...)) << "\n" << std::flush;
    }
};

extern Logger g_Logger;

#endif // LOG_LOGGER_H
