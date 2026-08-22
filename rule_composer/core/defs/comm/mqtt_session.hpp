/**
 * \file mqtt_session.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_MQTT_SESSION_HPP
#define RULE_COMPOSER_MQTT_SESSION_HPP

#include <comm/event_mqtt_received.hpp>
#include <mqtt/async_client.h>
#include <mqtt/callback.h>
#include <rule_composer_lib/util/event_listener.hpp>
#include <spdlog/spdlog.h>

namespace rule_composer::core::comm
{

    class mqtt_session : public mqtt::callback,
                         public lib::util::event_listener< event_mqtt_received >,
                         public lib::util::event_listener< event_mqtt_connection_status >
    {
    public:

        using lib::util::event_listener< event_mqtt_received >::add_event_listener;
        using lib::util::event_listener< event_mqtt_connection_status >::add_event_listener;

        explicit mqtt_session( const std::shared_ptr< spdlog::logger >& logger, const std::string& server_uri, const std::string& client_id );

        void connect( );
        void disconnect( );
        void subscribe( const std::string& topic, std::uint8_t qos );
        void unsubscribe( const std::string& topic );
        void publish( const std::string& topic, const std::string& payload, uint8_t qos, bool retain );

    private:

        std::shared_ptr< spdlog::logger >     logger;
        const std::string                     server_uri;
        const std::string                     client_id;
        std::unique_ptr< mqtt::async_client > client;

        void connected( const mqtt::string& ) override;
        void connection_lost( const mqtt::string& ) override;
        void delivery_complete( mqtt::delivery_token_ptr ) override;
        void message_arrived( mqtt::const_message_ptr ) override;
    };

} // namespace rule_composer::core::comm

#endif // RULE_COMPOSER_MQTT_SESSION_HPP
