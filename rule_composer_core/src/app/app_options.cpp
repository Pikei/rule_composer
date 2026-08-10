/**
 * \file app_options.cpp
 * Created by Piotr Karol 2026
 */
#include <app/app_options.hpp>

app_options::app_options() : options { PROGRAM_NAME, PROGRAM_HELP }
{
    auto general = options.add_options();
    general(PARAM_LOG_LEVEL, DESC_LOG_LEVEL, cxxopts::value<std::string>()->default_value("info"));
    general(PARAM_CONFIG_PATH, DESC_CONFIG_PATH, cxxopts::value<std::string>()->default_value(RUNTIME_CONFIG));
}

cxxopts::ParseResult app_options::parse(int& argc, const char**& argv)
{
    return options.parse(argc, argv);
}
