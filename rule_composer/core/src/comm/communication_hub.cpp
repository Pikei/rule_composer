/**
 * \file communication_hub.cpp
 * Created by Piotr Karol 2026
 */

#include <utility>

#include <comm/communication_hub.hpp>

namespace rule_composer::core::comm
{

    communication_hub::communication_hub( const std::shared_ptr< spdlog::logger >& logger ) : logger { logger }
    {
    }

    void communication_hub::mqtt_start( const std::string& server_uri, const std::string& client_id )
    {
        mqtt = std::make_unique< mqtt_session >( logger, server_uri, client_id );
        mqtt->connect( );
    }

    void communication_hub::mqtt_stop( )
    {
        mqtt->disconnect( );
        mqtt.release( );
    }

    void communication_hub::mqtt_subscribe( const std::string& topic, std::uint8_t qos )
    {
        mqtt->subscribe( topic, qos );
    }

    void communication_hub::mqtt_unsubscribe( const std::string& topic )
    {
        mqtt->unsubscribe( topic );
    }

    void communication_hub::mqtt_publish( const std::string& topic, const std::string& payload, std::uint8_t qos, std::uint8_t retained )
    {
        mqtt->publish( topic, payload, qos, retained );
    }

    void communication_hub::mqtt_add_event_listener( std::function< void( const event_mqtt_received& cb ) > callback )
    {
        mqtt->add_event_listener( std::move( callback ) );
    }

    void communication_hub::mqtt_add_event_listener( std::function< void( const event_mqtt_connection_status& cb ) > callback )
    {
        mqtt->add_event_listener( std::move( callback ) );
    }

} // namespace rule_composer::core::comm
