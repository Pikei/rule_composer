/**
 * \file sim_app.cpp
 * Created by Piotr Karol 2026
 */
#include <domain/enums/action_type.hpp>
#include <sim_app.hpp>

namespace rule_composer::simulator
{
    sim_app::sim_app( const cxxopts::ParseResult& args ) : application { args, sim_options::PROGRAM_NAME }
    {
    }

    void sim_app::before_run( )
    {
        id                     = args[sim_options::PARAM_ID].as< std::uint16_t >( );
        name                   = args[sim_options::PARAM_NAME].as< std::string >( );
        able_to_set_brightness = args[sim_options::PARAM_BRIGHTNESS].count( ) > 0;
        able_to_set_color      = args[sim_options::PARAM_COLOR].count( ) > 0;

        if ( able_to_set_brightness )
        {
            status.brightness = 100;
        }
        if ( able_to_set_color )
        {
            status.color = { 255, 255, 255 };
        }

        client = std::make_unique< mqtt::async_client >( "tcp://localhost:1883", "sim-light-" + std::to_string( id ) );
        client->set_callback( *this );

        mqtt::connect_options opts;
        opts.set_clean_session( true );
        client->connect( opts )->wait( );

        logger->info( "Connected to broker as '{}' (id={}), subscribing to '{}'", name, id, command_topic( ) );
        client->subscribe( command_topic( ), 1 );

        log_status( );
        publish_status( );
    }

    void sim_app::after_run( )
    {
        if ( client )
        {
            client->disconnect( )->wait( );
        }
    }
    void sim_app::message_arrived( mqtt::const_message_ptr message )
    {
        const std::string payload = message->to_string( );
        logger->debug( "Command received: {}", payload );

        try
        {
            const auto j = nlohmann::json::parse( payload );
            handle_command( j );
        }
        catch ( const std::exception& e )
        {
            logger->error( "Failed to parse command payload '{}': {}", payload, e.what( ) );
        }
    }

    void sim_app::connection_lost( const mqtt::string& cause )
    {
        logger->warn( "MQTT connection lost: {}", cause );
    }

    void sim_app::handle_command( const nlohmann::json& payload )
    {
        const auto str_type = payload.at( "type" ).get< std::string >( );
        const auto type     = str_to_action_type( str_type );
        switch ( type )
        {
            case domain::enums::action_type::turn_on_light:
                status.on = true;
                break;
            case domain::enums::action_type::turn_off_light:
                status.on = false;
                break;
            case domain::enums::action_type::set_brightness:
                handle_command_set_brightness( payload );
                break;
            case domain::enums::action_type::set_light_color:
                handle_command_set_color( payload );
                break;
            default:
                logger->warn( "Unknown command type: {}", str_type );
                return;
        }
        log_status( );
        publish_status( );
    }

    void sim_app::handle_command_set_brightness( const nlohmann::json& payload )
    {
        if ( !able_to_set_brightness )
        {
            logger->warn( "Device unable to set brightness - ignoring command" );
            return;
        }
        status.brightness = payload.at( "value" ).get< std::uint8_t >( );
    }

    void sim_app::handle_command_set_color( const nlohmann::json& payload )
    {
        if ( !able_to_set_color )
        {
            logger->warn( "Device unable to set color - ignoring command" );
            return;
        }
        const auto red   = payload.at( "value" ).at( "r" ).get< std::uint8_t >( );
        const auto green = payload.at( "value" ).at( "g" ).get< std::uint8_t >( );
        const auto blue  = payload.at( "value" ).at( "b" ).get< std::uint8_t >( );
        status.color     = { red, green, blue };
    }

    void sim_app::publish_status( )
    {
        nlohmann::json j;
        j["on"] = status.on;
        if ( status.brightness )
        {
            j["brightness"] = *status.brightness;
        }
        if ( status.color )
        {
            const auto& [r, g, b] = *status.color;
            j["color"]            = {
                { "r", r },
                { "g", g },
                { "b", b }
            };
        }

        client->publish( status_topic( ), j.dump( ), /*qos=*/1, /*retained=*/true );
    }

    void sim_app::log_status( )
    {
        logger->info( "" );
        logger->info( "############################" );
        logger->info( "DEVICE" );
        logger->info( "name: {} | id: {}", name, id );
        logger->info( "============================" );
        logger->info( "STATUS" );
        logger->info( "----------------------------" );
        if ( !status.on )
        {
            logger->info( "turned OFF" );
            logger->info( "############################" );
            logger->info( "" );
            return;
        }

        logger->info( "turned ON" );

        if ( able_to_set_brightness )
        {
            logger->info( "----------------------------" );
            logger->info( "brightness: {}%", status.brightness.value( ) );
        }

        if ( able_to_set_color )
        {
            logger->info( "----------------------------" );
            logger->info( "RGB color: ({},{},{})", status.color.value( ).r, status.color.value( ).g, status.color.value( ).b );
        }
        logger->info( "#############################" );
        logger->info( "" );
    }

    std::string sim_app::command_topic( ) const
    {
        return "rule_composer/command/light/" + std::to_string( id );
    }

    std::string sim_app::status_topic( ) const
    {
        return "rule_composer/status/light/" + std::to_string( id );
    }

} // namespace rule_composer::simulator
