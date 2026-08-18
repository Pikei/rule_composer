/**
 * \file application.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LIBRARY_APPLICATION_HPP
#define RULE_COMPOSER_LIBRARY_APPLICATION_HPP

#include <memory>

#include <cxxopts.hpp>
#include <rule_composer_lib/util/event_loop.hpp>
#include <spdlog/logger.h>

namespace rule_composer::lib::app
{
    namespace logger_constants
    {
        constexpr auto DEFAULT_LOGGER_NAME = "console";
        constexpr auto DEFAULT_LOG_PATTERN = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] | %v";
    } // namespace logger_constants

    class application
    {
    public:

        explicit application( const cxxopts::ParseResult& args, const std::string& prog_name );
        virtual ~application( ) = default;

        void run( );

    protected:

        cxxopts::ParseResult              args;
        std::shared_ptr< spdlog::logger > logger;
        std::string                       program_name;
        util::event_loop                  loop;

        virtual void before_run( ) { /*empty*/ };
        virtual void after_run( ) { /*empty*/ };

    private:

        spdlog::level::level_enum                parse_arg_log_level( ) const;
        std::shared_ptr< spdlog::logger >        configure_logger( ) const;
        static std::shared_ptr< spdlog::logger > create_logger( const std::string&        logger_name,
                                                                spdlog::level::level_enum log_level,
                                                                const std::string&        pattern = logger_constants::DEFAULT_LOG_PATTERN );
    };
} // namespace rule_composer::lib::app

#endif // RULE_COMPOSER_LIBRARY_APPLICATION_HPP
