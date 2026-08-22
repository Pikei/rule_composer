/**
 * \file app_options.cpp
 * Created by Piotr Karol 2026
 */
#include <app/app_options.hpp>

namespace rule_composer::core::app
{
    app_options::app_options( ) : lib::app::app_options { PROGRAM_NAME, PROGRAM_HELP }
    {
        auto general = options.add_options( );
        general( PARAM_CONFIG_PATH, DESC_CONFIG_PATH, cxxopts::value< std::string >( )->default_value( RUNTIME_CONFIG ) );
        general( PARAM_EVAL_INTERVAL, DESC_EVAL_INTERVAL, cxxopts::value< std::uint32_t >( )->default_value( "10000" ) );
        general( PARAM_MQTT_RECONNECT_INTERVAL, DESC_MQTT_RECONNECT_INTERVAL, cxxopts::value< std::uint8_t >( )->default_value( "5" ) );
        general( PARAM_MQTT_BROKER_URI, DESC_MQTT_BROKER_URI, cxxopts::value< std::string >( )->default_value( "tcp://localhost:1883" ) );
        general( PARAM_MQTT_ID, DESC_MQTT_ID, cxxopts::value< std::string >( )->default_value( "rule_composer_core" ) );
    }
} // namespace rule_composer::core::app
