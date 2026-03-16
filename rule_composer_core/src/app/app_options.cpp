/**
 * \file app_options.cpp
 * Created by Piotr Karol 2026
 */
#include <app/app_options.hpp>
#include <spdlog/common.h>
inline std::istream& operator>>(std::istream& in, spdlog::level::level_enum& level)
{
    std::string key;
    in >> key;

    static const std::unordered_map<std::string, spdlog::level::level_enum> level_map = {
        { "trace", spdlog::level::trace },
        { "debug", spdlog::level::debug },
        { "info", spdlog::level::info },
        { "warn", spdlog::level::warn },
        { "error", spdlog::level::err },
        { "critical", spdlog::level::critical },
        { "off", spdlog::level::off }
    };

    auto it = level_map.find(key);
    if (it != level_map.end())
    {
        level = it->second;
    }
    else
    {
        throw std::invalid_argument("Invalid log-level: " + key);
    }

    return in;
}

app_options::app_options() : options { PROGRAM_NAME, PROGRAM_HELP }
{
    auto general = options.add_options();
    general(PARAM_LOG_LEVEL, DESC_LOG_LEVEL, cxxopts::value<std::string>()->default_value("info"));
    general(PARAM_CONFIG_PATH, DESC_CONFIG_PATH, cxxopts::value<std::string>()->default_value("./config/config.json"));
}

cxxopts::ParseResult app_options::parse(int& argc, const char**& argv)
{
    return options.parse(argc, argv);
}
