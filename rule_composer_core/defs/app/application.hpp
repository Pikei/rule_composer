/**
 * \file application.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_APPLICATION_HPP
#define RULE_COMPOSER_APPLICATION_HPP

#include <cxxopts.hpp>
#include <memory>
#include <spdlog/spdlog.h>

using log_level_map_t = std::unordered_map<std::string, spdlog::level::level_enum>;

class application
{
public:
    explicit application(const cxxopts::ParseResult& args);

protected:
    cxxopts::ParseResult            args;
    std::shared_ptr<spdlog::logger> logger;

private:
    static constexpr auto           default_logger_name = "console";
    std::shared_ptr<spdlog::logger> configure_logger();
    spdlog::level::level_enum       parse_arg_log_level();
};

#endif // RULE_COMPOSER_APPLICATION_HPP
