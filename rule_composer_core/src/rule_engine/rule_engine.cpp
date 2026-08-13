/**
 * \file rule_engine.cpp
 * Created by Piotr Karol 2026
 */

#include <rule_engine/rule_engine.hpp>
#include <rules/conditions/condition_group.hpp>
#include <util/domain_factory.hpp>

rule_engine::rule_engine( event_loop& loop, std::shared_ptr< spdlog::logger >& logger_ ) :
    timer { loop.create_repeat_timer( std::chrono::milliseconds { 3000 }, [this] { evaluate_rules( ); } ) },
    logger { logger_ }
{
}

void rule_engine::parse_config_dto( const configuration_dto& config )
{
    for ( const auto& d_dto : config.devices )
    {
        for ( const auto& r_dto : d_dto.rules )
        {
            rules.emplace( d_dto.id, domain_factory::create_rule( r_dto ) );
            triggered.emplace( r_dto.id, false );
        }
    }
}

void rule_engine::start( )
{
    timer.start( );
}

void rule_engine::evaluate_rules( )
{
    logger->info( "evaluating rules ..." );
    for ( const auto& r : rules )
    {
        const auto& condition      = r.second.get_condition( );
        const bool  should_trigger = ( condition.evaluate( ctx ) ) && ( !triggered.at( r.second.get_id( ) ) );
        if ( should_trigger )
        {
            logger->info( "triggering action chain in rule {} for device {}", r.second.get_id( ), r.first );
            triggered.at( r.second.get_id( ) ) = true;
        }
    }
}
