#ifndef CONFIG_CONFIG_H
#define CONFIG_CONFIG_H

#include <string>

class IConfig
{
public:
    virtual ~IConfig() = default;

    virtual bool Load(const std::string &Name) = 0;

    virtual int GetInt(const std::string &Name, int Fallback) = 0;
    virtual int64_t GetInt64(const std::string &Name, int64_t Fallback) = 0;
    virtual std::string GetString(const std::string &Name, std::string Fallback) = 0;
};

#endif // CONFIG_CONFIG_H
