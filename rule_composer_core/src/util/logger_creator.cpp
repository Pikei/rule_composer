/**
 * \file logger_creator.cpp
 * Created by Piotr Karol 2026
 */

#include <util/logger_creator.hpp>

#include <spdlog/sinks/stdout_color_sinks-inl.h>

std::shared_ptr<spdlog::logger> logger_creator::create_logger(const std::string& logger_name, spdlog::level::level_enum log_level, const std::string& pattern)
{
    auto log = spdlog::stdout_color_mt(logger_name);
    log->set_level(log_level);
    log->set_pattern(pattern);
    return log;
}