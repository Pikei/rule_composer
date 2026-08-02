/**
 * \file logger_creator.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LOGGER_CREATOR_HPP
#define RULE_COMPOSER_LOGGER_CREATOR_HPP

#include <memory>
#include <spdlog/logger.h>

class logger_creator
{
public:
    static std::shared_ptr<spdlog::logger> create_logger(const std::string& logger_name, spdlog::level::level_enum log_level = spdlog::level::info, const std::string& pattern = logger_pattern);
    static constexpr auto                  logger_pattern = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] | %v";
};

#endif // RULE_COMPOSER_LOGGER_CREATOR_HPP
