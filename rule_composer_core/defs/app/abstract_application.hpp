/**
 * \file abstract_application.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ABSTRACT_APPLICATION_HPP
#define RULE_COMPOSER_ABSTRACT_APPLICATION_HPP

#include <memory>

#include <app/event_loop.hpp>
#include <cxxopts.hpp>
#include <spdlog/logger.h>

using logger_ptr = std::shared_ptr< spdlog::logger >;

namespace logger_constants
{
    constexpr auto DEFAULT_LOGGER_NAME = "console";
    constexpr auto DEFAULT_LOG_PATTERN = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] | %v";
} // namespace logger_constants

class abstract_application
{
public:

    explicit abstract_application( const cxxopts::ParseResult& args, const std::string& prog_name );
    virtual ~abstract_application( ) = default;

    void run( );

protected:

    cxxopts::ParseResult args;
    logger_ptr           logger;
    std::string          program_name;
    event_loop           loop;

    virtual void before_run( ) { /*empty*/ };
    virtual void after_run( ) { /*empty*/ };

private:

    spdlog::level::level_enum parse_arg_log_level( ) const;
    logger_ptr                configure_logger( ) const;
    static logger_ptr
    create_logger( const std::string& logger_name, spdlog::level::level_enum log_level, const std::string& pattern = logger_constants::DEFAULT_LOG_PATTERN );
};

#endif // RULE_COMPOSER_ABSTRACT_APPLICATION_HPP
