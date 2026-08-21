/**
 * \file mqtt_command_visitor.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_MQTT_COMMAND_VISITOR_HPP
#define RULE_COMPOSER_MQTT_COMMAND_VISITOR_HPP

#include <nlohmann/json.hpp>
#include <util/command_visitor.hpp>

namespace rule_composer::core::util
{

    class mqtt_command_visitor : public command_visitor
    {
    public:

        void visit( const domain::rules::commands::light::turn_on& cmd ) override;
        void visit( const domain::rules::commands::light::turn_off& cmd ) override;
        void visit( const domain::rules::commands::light::set_brightness& cmd ) override;
        void visit( const domain::rules::commands::light::set_color& cmd ) override;
        void visit( const domain::rules::commands::curtains::open& cmd ) override;
        void visit( const domain::rules::commands::curtains::close& cmd ) override;
        void visit( const domain::rules::commands::curtains::set_position& cmd ) override;
        void visit( const domain::rules::commands::socket::turn_on& cmd ) override;
        void visit( const domain::rules::commands::socket::turn_off& cmd ) override;
        void visit( const domain::rules::commands::thermostat::set_temperature& cmd ) override;

        [[nodiscard]]
        std::string get_payload( ) const;

    private:

        nlohmann::json payload;
    };

} // namespace rule_composer::core::util

#endif // RULE_COMPOSER_MQTT_COMMAND_VISITOR_HPP
