#ifndef ALALBALOG_H
#define ALALBALOG_H

#include "AlalbaEngine.h"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

namespace Alalba
{
    class AlalbaLog
    {
    public:
        AlalbaLog() = delete;
        AlalbaLog(const AlalbaLog&) = delete;
        AlalbaLog &operator=(const AlalbaLog&) = delete;
        static void Init();
        static spdlog::logger* GetLoggerInstance()
        {
            assert(sLoggerInstance && "Logger instance is NULL");
            return sLoggerInstance.get();
        }

    private:
        static std::shared_ptr<spdlog::logger> sLoggerInstance;
    };
#define LOG_T(...) SPDLOG_LOGGER_TRACE(Alalba::AlalbaLog::GetLoggerInstance(), __VA_ARGS__)
#define LOG_D(...) SPDLOG_LOGGER_DEBUG(Alalba::AlalbaLog::GetLoggerInstance(), __VA_ARGS__)
#define LOG_I(...) SPDLOG_LOGGER_INFO(Alalba::AlalbaLog::GetLoggerInstance(), __VA_ARGS__)
#define LOG_W(...) SPDLOG_LOGGER_WARN(Alalba::AlalbaLog::GetLoggerInstance(), __VA_ARGS__)
#define LOG_E(...) SPDLOG_LOGGER_ERROR(Alalba::AlalbaLog::GetLoggerInstance(), __VA_ARGS__)
}

#endif