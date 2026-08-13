/**
 * \file rule_engine.cpp
 * Created by Piotr Karol 2026
 */

#include <rule_engine/rule_engine.hpp>

rule_engine::rule_engine( event_loop& loop, std::shared_ptr< spdlog::logger >& logger_, configuration_dto& config ) :
    timer { loop.create_repeat_timer( std::chrono::milliseconds { 1000 }, [this] { evaluate_rules( ); } ) },
    logger { logger_ }
{
    // TODO: config_dto parser
}

void rule_engine::start( )
{
    timer.start( );
}

void rule_engine::evaluate_rules( )
{
    logger->info( "evaluating rules ..." );
}
