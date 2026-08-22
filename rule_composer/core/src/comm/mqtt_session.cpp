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
        client->connect( opts )->wait( );
        logger->info( "MQTT session connected to broker: {}", server_uri );
    }

    void mqtt_session::disconnect( )
    {
        client->disconnect( );
        std::string disconnect_reason = "MQTT session disconnected successfully.";
        logger->info( disconnect_reason );
        event_listener< event_mqtt_connection_status >::notify( { false, disconnect_reason } );
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
        event_listener< event_mqtt_connection_status >::notify( { true } );
    }

    void mqtt_session::connection_lost( const mqtt::string& cause )
    {
        logger->warn( "MQTT connection lost: {}", cause );
        event_listener< event_mqtt_connection_status >::notify( { false, cause } );
    }

    void mqtt_session::delivery_complete( mqtt::delivery_token_ptr element )
    {
        logger->debug( "MQTT session delivered: {}", element->get_message( )->to_string( ) );
    }

    void mqtt_session::message_arrived( mqtt::const_message_ptr message )
    {
        logger->debug( "MQTT session message: {}", message->get_topic( ) );
        event_listener< event_mqtt_received >::notify( event_mqtt_received { message->get_topic( ), message->get_payload_str( ) } );
    }

} // namespace rule_composer::core::comm
