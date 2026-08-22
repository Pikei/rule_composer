/**
 * \file app_options.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_APP_OPTIONS_HPP
#define RULE_COMPOSER_APP_OPTIONS_HPP

#include <rule_composer_lib/app/app_options.hpp>

namespace rule_composer::core::app
{
    class app_options : public lib::app::app_options
    {
    public:

        explicit app_options( );

        static constexpr auto PROGRAM_NAME = "rule_composer_core";
        static constexpr auto PROGRAM_HELP = "help";

        static constexpr auto PARAM_CONFIG_PATH = "config-path";
        static constexpr auto DESC_CONFIG_PATH  = "Optional parameter used to specify path to configuration file.";

        static constexpr auto PARAM_EVAL_INTERVAL = "eval-interval";
        static constexpr auto DESC_EVAL_INTERVAL  = "Optional parameter used to specify interval of evaluation of rules conditions in milliseconds.";

        static constexpr auto PARAM_MQTT_RECONNECT_INTERVAL = "mqtt-reconnect-interval";
        static constexpr auto DESC_MQTT_RECONNECT_INTERVAL  = "Optional parameter used to specify the retry interval for opening an MQTT session in seconds.";

        static constexpr auto PARAM_MQTT_BROKER_URI = "mqtt-broker-uri";
        static constexpr auto DESC_MQTT_BROKER_URI  = "Optional parameter used to specify MQTT broker URI";

        static constexpr auto PARAM_MQTT_ID = "mqtt-id";
        static constexpr auto DESC_MQTT_ID  = "Optional parameter used to specify MQTT client ID";
    };
} // namespace rule_composer::core::app

#endif // RULE_COMPOSER_APP_OPTIONS_HPP
