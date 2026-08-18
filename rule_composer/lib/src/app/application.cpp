/**
 * \file application.cpp
 * Created by Piotr Karol 2026
 */

#include <iostream>

#include <rule_composer_lib/app/app_options.hpp>
#include <rule_composer_lib/app/application.hpp>
#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace rule_composer::lib::app
{
    application::application( const cxxopts::ParseResult& args, const std::string& prog_name ) :
        args( args ),
        logger { configure_logger( ) },
        program_name { prog_name }
    {
    }

    void application::run( )
    {
        logger->info( "Application {} started", program_name );
        before_run( );
        loop.run( );
        after_run( );
        logger->info( "Application {} stopped", program_name );
    }

    std::shared_ptr< spdlog::logger > application::configure_logger( ) const
    {
        spdlog::level::level_enum log_level;
        if ( 0 < args[app_options::PARAM_LOG_LEVEL].count( ) )
        {
            try
            {
                log_level = parse_arg_log_level( );
            }
            catch ( std::invalid_argument& e )
            {
                std::cerr << e.what( ) << std::endl;
                std::cout << "Setting default logger level..." << std::endl;
                log_level = spdlog::level::info;
            }
        }
        else
        {
            log_level = spdlog::level::trace;
        }

        return create_logger( logger_constants::DEFAULT_LOGGER_NAME, log_level );
    }

    spdlog::level::level_enum application::parse_arg_log_level( ) const
    {
        const auto log_level_str = args[app_options::PARAM_LOG_LEVEL].as< std::string >( );
        if ( log_level_str.empty( ) )
        {
            throw std::invalid_argument( "Argument log-level is empty." );
        }

        const std::unordered_map< std::string, spdlog::level::level_enum > level_map = {
            { "trace",    spdlog::level::trace    },
            { "debug",    spdlog::level::debug    },
            { "info",     spdlog::level::info     },
            { "warn",     spdlog::level::warn     },
            { "error",    spdlog::level::err      },
            { "critical", spdlog::level::critical },
            { "off",      spdlog::level::off      }
        };

        auto it = level_map.find( log_level_str );
        if ( it != level_map.end( ) )
        {
            return it->second;
        }
        throw std::invalid_argument( "Invalid log-level: " + log_level_str );
    }

    std::shared_ptr< spdlog::logger >
    application::create_logger( const std::string& logger_name, const spdlog::level::level_enum log_level, const std::string& pattern )
    {
        auto log = spdlog::stdout_color_mt( logger_name );
        log->set_level( log_level );
        log->set_pattern( pattern );
        return log;
    }
} // namespace rule_composer::lib::app
