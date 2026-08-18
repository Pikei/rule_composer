/**
 * \file rule_engine.cpp
 * Created by Piotr Karol 2026
 */

#include <app/rule_engine.hpp>
#include <util/domain_factory.hpp>

namespace rule_composer::core::app
{
    rule_engine::rule_engine( lib::util::event_loop& loop, std::shared_ptr< spdlog::logger >& logger_, std::uint32_t eval_interval_ ) :
        timer { loop, std::chrono::milliseconds { eval_interval_ }, [this] { evaluate_rules( ); } },
        logger { logger_ }
    {
    }

    void rule_engine::parse_config_dto( const dto::configuration_dto& config )
    {
        for ( const auto& d_dto : config.devices )
        {
            for ( const auto& r_dto : d_dto.rules )
            {
                rules.emplace( d_dto.id, util::domain_factory::create_rule( r_dto ) );
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
        logger->debug( "evaluating rules ..." );
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
} // namespace rule_composer::core::app
