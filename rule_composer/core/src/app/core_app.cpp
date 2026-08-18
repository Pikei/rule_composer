/**
 * \file core_app.cpp
 * Created by Piotr Karol 2026
 */

#include <app/app_options.hpp>
#include <app/core_app.hpp>

namespace rule_composer::core::app
{

    core_app::core_app( const cxxopts::ParseResult& args ) :
        application { args, app_options::PROGRAM_NAME },
        parser { args[app_options::PARAM_CONFIG_PATH].as< std::string >( ), logger }
    {
    }

    void core_app::before_run( )
    {
        try
        {
            config_dto = parser.parse_config( );
        }
        catch ( std::exception& e )
        {
            logger->error( "Configuration parsing error: " + std::string { e.what( ) } );
        }
        engine = std::make_unique< rule_engine >( loop, logger, args[app_options::PARAM_EVAL_INTERVAL].as< std::uint32_t >( ) );
        engine->parse_config_dto( config_dto );
        engine->start( );
    }
} // namespace rule_composer::core::app
