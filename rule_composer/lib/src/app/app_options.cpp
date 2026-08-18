/**
 * \file app_options.cpp
 * Created by Piotr Karol 2026
 */

#include <rule_composer_lib/app/app_options.hpp>

namespace rule_composer::lib::app
{
    app_options::app_options( const std::string& program_name, const std::string& program_help ) : options { program_name, program_help }
    {
        auto opts = options.add_options( );
        opts( PARAM_LOG_LEVEL, DESC_LOG_LEVEL, cxxopts::value< std::string >( )->default_value( "info" ) );
    }

    cxxopts::ParseResult app_options::parse( int& argc, const char**& argv )
    {
        return options.parse( argc, argv );
    }

} // namespace rule_composer::lib::app
