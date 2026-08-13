/**
 * \file application.cpp
 * Created by Piotr Karol 2026
 */

#include <app/app_options.hpp>
#include <app/application.hpp>

application::application( const cxxopts::ParseResult& args ) :
    abstract_application { args, app_options::PROGRAM_NAME },
    parser { args[app_options::PARAM_CONFIG_PATH].as< std::string >( ), logger }
{
}

void application::before_run( )
{
    try
    {
        config_dto = parser.parse_config( );
    }
    catch ( std::exception& e )
    {
        logger->error( "Configuration parsing error: " + std::string { e.what( ) } );
    }
    engine = std::make_unique< rule_engine >( loop, logger );
    engine->parse_config_dto( config_dto );
    engine->start( );
}
