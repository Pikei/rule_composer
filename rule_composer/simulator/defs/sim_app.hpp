/**
 * \file sim_app.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_SIM_APP_HPP
#define RULE_COMPOSER_SIM_APP_HPP

#include <light_status.hpp>
#include <mqtt/async_client.h>
#include <mqtt/callback.h>
#include <nlohmann/json.hpp>
#include <rule_composer_lib/app/application.hpp>
#include <sim_options.hpp>

namespace rule_composer::simulator
{

    class sim_app : public lib::app::application,
                    public mqtt::callback
    {
    public:

        explicit sim_app( const cxxopts::ParseResult& args );

    protected:

        void before_run( ) override;
        void after_run( ) override;

    public:

        std::uint16_t                         id = 0;
        std::string                           name;
        bool                                  able_to_set_brightness = false;
        bool                                  able_to_set_color      = false;
        std::unique_ptr< mqtt::async_client > client;
        light_status                          status;

        void message_arrived( mqtt::const_message_ptr ) override;
        void connection_lost( const mqtt::string& ) override;
        void handle_command( const nlohmann::json& payload );
        void handle_command_set_brightness( const nlohmann::json& payload );
        void handle_command_set_color( const nlohmann::json& payload );

        void publish_status( );
        void log_status( );

        [[nodiscard]]
        std::string command_topic( ) const;

        [[nodiscard]]
        std::string status_topic( ) const;
    };

} // namespace rule_composer::simulator

#endif // RULE_COMPOSER_SIM_APP_HPP
