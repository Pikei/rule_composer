/**
 * \file application.cpp
 * Created by Piotr Karol 2026
 */
#include <app/app_options.hpp>
#include <app/application.hpp>

#include <iostream>
#include <spdlog/sinks/stdout_color_sinks-inl.h>

application::application(const cxxopts::ParseResult& args) : args(args), logger { configure_logger() }
{
    logger->info("Application {} started", app_options::PROGRAM_NAME);
}

spdlog::level::level_enum application::parse_arg_log_level()
{
    const auto log_level_str = args[app_options::PARAM_LOG_LEVEL].as<std::string>();
    if (log_level_str.empty())
    {
        throw std::invalid_argument("Argument log-level is empty.");
    }

    const log_level_map_t level_map = {
        { "trace", spdlog::level::trace },
        { "debug", spdlog::level::debug },
        { "info", spdlog::level::info },
        { "warn", spdlog::level::warn },
        { "error", spdlog::level::err },
        { "critical", spdlog::level::critical },
        { "off", spdlog::level::off }
    };

    auto it = level_map.find(log_level_str);
    if (it != level_map.end())
    {
        return it->second;
    }
    throw std::invalid_argument("Invalid log-level: " + log_level_str);
}

std::shared_ptr<spdlog::logger> application::configure_logger()
{
    auto log = spdlog::stdout_color_mt("console");
    if (0 < args[app_options::PARAM_LOG_LEVEL].count())
    {
        try
        {
            log->set_level(parse_arg_log_level());
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            std::cout << "Setting default logger level..." << std::endl;
            log->set_level(spdlog::level::info);
        }
    }
    else
    {
        log->set_level(spdlog::level::trace);
    }

    log->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l]  %v");

    return log;
}
