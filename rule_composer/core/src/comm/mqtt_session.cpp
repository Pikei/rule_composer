/**
 * \file mqtt_session.cpp
 * Created by Piotr Karol 2026
 */

#include <comm/mqtt_session.hpp>

namespace rule_composer::core::comm
{

    mqtt_session::mqtt_session( const std::shared_ptr< spdlog::logger >& logger, const std::string& server_uri, const std::string& client_id ) :
        logger { logger },
        server_uri { server_uri },
        client_id { client_id }
    {
    }

    void mqtt_session::connect( )
    {
        client = std::make_unique< mqtt::async_client >( server_uri, client_id );
        client->set_callback( *this );
        mqtt::connect_options opts;
        opts.set_automatic_reconnect( true );
        opts.set_clean_session( true );

        try
        {
            client->connect( opts )->try_wait( );
            logger->info( "MQTT session connected to broker: {}", server_uri );
        }
        catch ( const mqtt::exception& e )
        {
            logger->error( e.what( ) );
        }
    }

    void mqtt_session::disconnect( )
    {
        client->disconnect( );
        logger->info( "MQTT session disconnected." );
    }

    void mqtt_session::subscribe( const std::string& topic, std::uint8_t qos )
    {
        client->subscribe( topic, qos );
    }

    void mqtt_session::unsubscribe( const std::string& topic )
    {
        client->unsubscribe( topic );
    }

    void mqtt_session::publish( const std::string& topic, const std::string& payload, std::uint8_t qos, bool retain )
    {
        client->publish( topic, payload, qos, retain );
        logger->debug( "MQTT session published: [topic: {} | message: {}]", topic, payload );
    }

    void mqtt_session::connected( const mqtt::string& cause )
    {
        logger->info( "MQTT session connected: {}", cause );
    }

    void mqtt_session::connection_lost( const mqtt::string& cause )
    {
        logger->warn( "MQTT connection lost: {}", cause );
    }

    void mqtt_session::delivery_complete( mqtt::delivery_token_ptr element )
    {
        logger->debug( "MQTT session delivered: {}", element->get_message( )->to_string( ) );
    }

    void mqtt_session::message_arrived( mqtt::const_message_ptr message )
    {
        // TODO: callback to communication_hub
    }

} // namespace rule_composer::core::comm
