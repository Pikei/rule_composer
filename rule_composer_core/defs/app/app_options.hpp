/**
 * \file app_options.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_APP_OPTIONS_HPP
#define RULE_COMPOSER_APP_OPTIONS_HPP

#include <spdlog/common.h>

#include <cxxopts.hpp>

class app_options
{
public:
    explicit app_options();

    cxxopts::ParseResult parse(int& argc, const char**& argv);

    static constexpr auto PROGRAM_NAME      = "rule_composer_core";
    static constexpr auto PROGRAM_HELP      = "help";

    static constexpr auto PARAM_LOG_LEVEL   = "log-level";
    static constexpr auto DESC_LOG_LEVEL    = "Optional parameter used to specify the application logger level (trace|debug|info|warn|error|critical|off).";

    static constexpr auto PARAM_CONFIG_PATH = "config-path";
    static constexpr auto DESC_CONFIG_PATH  = "Optional parameter used to specify path to configuration file.";

private:
    cxxopts::Options options;
};

#endif // RULE_COMPOSER_APP_OPTIONS_HPP
