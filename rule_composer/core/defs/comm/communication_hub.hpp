/**
 * \file communication_hub.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_COMMUNICATION_HUB_HPP
#define RULE_COMPOSER_COMMUNICATION_HUB_HPP

#include <memory>

#include <comm/mqtt_session.hpp>
#include <spdlog/logger.h>

namespace rule_composer::core::comm
{

    class communication_hub
    {
    public:

        explicit communication_hub( const std::shared_ptr< spdlog::logger >& logger );

        void mqtt_start( const std::string& server_uri, const std::string& client_id );
        void mqtt_stop( );
        void mqtt_subscribe( const std::string& topic, std::uint8_t qos );
        void mqtt_unsubscribe( const std::string& topic );
        void mqtt_publish( const std::string& topic, const std::string& payload, uint8_t qos, uint8_t retained );
        void mqtt_add_event_listener( std::function< void( const event_mqtt_received& cb ) > callback );
        void mqtt_add_event_listener( std::function< void( const event_mqtt_connection_status& cb ) > callback );

    private:

        // TODO: Callback to application
        std::unique_ptr< mqtt_session >   mqtt;
        std::shared_ptr< spdlog::logger > logger;
    };

} // namespace rule_composer::core::comm

#endif // RULE_COMPOSER_COMMUNICATION_HUB_HPP
