/**
 * \file core_app.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_APPLICATION_HPP
#define RULE_COMPOSER_APPLICATION_HPP

#include <app/rule_engine.hpp>
#include <rule_composer_lib/app/application.hpp>
#include <util/config_parser.hpp>

#include "comm/communication_hub.hpp"
#include "rule_composer_lib/util/timeout_timer.hpp"

namespace rule_composer::core::app
{
    class core_app : public lib::app::application
    {
    public:

        explicit core_app( const cxxopts::ParseResult& args );

    private:

        static constexpr auto CORE_SUB_TOPIC = "rule_composer/status/#";
        static constexpr int  CORE_SUB_QOS   = 1;

        util::config_parser                        parser;
        dto::configuration_dto                     config_dto;
        std::unique_ptr< rule_engine >             engine;
        std::unique_ptr< comm::communication_hub > comm_hub;
        domain::rules::context                     ctx;
        lib::util::timeout_timer                   connect_timer;
        bool                                       mqtt_session_connected = false;

        void before_run( ) override;
        void mqtt_device_status_received( const event_mqtt_received& ev );
        void mqtt_connection_status_changed( const event_mqtt_connection_status& ev );
        void open_mqtt_session( );
    };
} // namespace rule_composer::core::app

#endif // RULE_COMPOSER_APPLICATION_HPP
