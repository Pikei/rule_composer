/**
 * \file event_mqtt_received.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_EVENT_MQTT_RECEIVED_HPP
#define RULE_COMPOSER_EVENT_MQTT_RECEIVED_HPP

#include <string>

struct event_mqtt_received
{
    std::string topic;
    std::string payload;
};

struct event_mqtt_connection_status
{
    bool        connected;
    std::string cause;
};

#endif // RULE_COMPOSER_EVENT_MQTT_RECEIVED_HPP
