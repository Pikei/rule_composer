/**
 * \file core_app.cpp
 * Created by Piotr Karol 2026
 */

#include <app/app_options.hpp>
#include <app/core_app.hpp>
#include <rule_composer_lib/util/str_util.hpp>

namespace rule_composer::core::app
{

    core_app::core_app( const cxxopts::ParseResult& args ) :
        application { args, app_options::PROGRAM_NAME },
        parser { args[app_options::PARAM_CONFIG_PATH].as< std::string >( ), logger },
        connect_timer { loop,
                        std::chrono::seconds { args[app_options::PARAM_MQTT_RECONNECT_INTERVAL].as< std::uint8_t >( ) },
                        [this] { open_mqtt_session( ); } }
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
        engine = std::make_unique< rule_engine >( loop, logger, args[app_options::PARAM_EVAL_INTERVAL].as< std::uint32_t >( ), ctx );
        engine->parse_config_dto( config_dto );

        comm_hub = std::make_unique< comm::communication_hub >( logger );
        open_mqtt_session( );
    }

    void core_app::mqtt_device_status_received( const event_mqtt_received& ev )
    {
        if ( lib::util::str_util::str_to_vector( ev.topic, '/' ).at( 2 ) != to_string( domain::enums::device_type::sensor ) )
        {
            return;
        }
        nlohmann::json payload;
        try
        {
            payload = nlohmann::json::parse( ev.payload );
        }
        catch ( std::exception& e )
        {
            logger->warn( "Received status should be in JSON format. [ topic:{} | payload:{} ] {}", ev.topic, ev.payload, e.what( ) );
            return;
        }

        std::string key = to_string( domain::enums::condition_type::temperature );
        if ( payload.contains( key ) )
        {
            ctx.set_temperature( payload.at( key ).get< double >( ) );
        }

        key = to_string( domain::enums::condition_type::humidity );
        if ( payload.contains( key ) )
        {
            ctx.set_humidity( payload.at( key ).get< double >( ) );
        }
    }

    void core_app::mqtt_connection_status_changed( const event_mqtt_connection_status& ev )
    {
        mqtt_session_connected = ev.connected;
        if ( !mqtt_session_connected )
        {
            logger->info( ev.cause );
            engine->stop( );
            connect_timer.start( );
        }
    }

    void core_app::open_mqtt_session( )
    {
        if ( mqtt_session_connected )
        {
            connect_timer.stop( );
            return;
        }
        try
        {
            comm_hub->mqtt_start( args[app_options::PARAM_MQTT_BROKER_URI].as< std::string >( ), args[app_options::PARAM_MQTT_ID].as< std::string >( ) );
            comm_hub->mqtt_subscribe( CORE_SUB_TOPIC, CORE_SUB_QOS );
            comm_hub->mqtt_add_event_listener( [this]( const event_mqtt_received& ev ) { mqtt_device_status_received( ev ); } );
            comm_hub->mqtt_add_event_listener( [this]( const event_mqtt_connection_status& ev ) { mqtt_connection_status_changed( ev ); } );
            engine->start( );
        }
        catch ( const mqtt::exception& e )
        {
            auto recon_delay = args[app_options::PARAM_MQTT_RECONNECT_INTERVAL].as< std::uint8_t >( );
            logger->error( "Couldn't open MQTT session. Cause: {}", e.what( ) );
            logger->error( "Ensure that broker is active. An attempt to reconnect will be made in {} seconds", recon_delay );
            engine->stop( );
            connect_timer.start( );
        }
    }

} // namespace rule_composer::core::app
