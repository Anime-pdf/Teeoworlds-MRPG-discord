#ifndef CONFIG_CONFIG_ENV_H
#define CONFIG_CONFIG_ENV_H

#include "config.h"

#include <optional>

class EnvConfig final : public IConfig
{
    static std::optional<std::string> GetEnvVar(const std::string& key) {
        if (const char* val = std::getenv(key.c_str())) {
            return std::string(val);
        }
        return std::nullopt;
    }

public:
    bool Load(const std::string &Name) override { return true; }

    int GetInt(const std::string &Name, int Fallback) override
    {
        auto TmpRes = GetEnvVar(Name);
        if(!TmpRes.has_value() || TmpRes->empty())
            return Fallback;
        try {
            return std::stoi(TmpRes.value());
        } catch (std::exception e) {
            return Fallback;
        }
    };
    int64_t GetInt64(const std::string &Name, int64_t Fallback) override
    {
        auto TmpRes = GetEnvVar(Name);
        if(!TmpRes.has_value() || TmpRes->empty())
            return Fallback;
        try {
            return std::stoll(TmpRes.value());
        } catch (std::exception e) {
            return Fallback;
        }
    }
    std::string GetString(const std::string &Name, std::string Fallback) override
    {
        auto TmpRes = GetEnvVar(Name);
        if(!TmpRes.has_value() || TmpRes->empty())
            return Fallback;
        return TmpRes.value();
    }
};

#endif // CONFIG_CONFIG_ENV_H
