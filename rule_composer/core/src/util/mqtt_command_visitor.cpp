/**
 * \file mqtt_command_visitor.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/enums/action_type.hpp>
#include <util/mqtt_command_visitor.hpp>

#include "domain/rules/commands/curtains/set_position.hpp"
#include "domain/rules/commands/light/set_brightness.hpp"
#include "domain/rules/commands/light/set_color.hpp"
#include "domain/rules/commands/thermostat/set_temperature.hpp"

namespace rule_composer::core::util
{
    void mqtt_command_visitor::visit( const domain::rules::commands::light::turn_on& cmd )
    {
        payload = {
            { "type", to_string( domain::enums::action_type::turn_on_light ) }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::light::turn_off& cmd )
    {
        payload = {
            { "type", to_string( domain::enums::action_type::turn_off_light ) }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::light::set_brightness& cmd )
    {
        payload = {
            { "type",  to_string( domain::enums::action_type::set_brightness ) },
            { "value", cmd.get_brightness( )                                   }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::light::set_color& cmd )
    {
        payload = {
            { "type", to_string( domain::enums::action_type::set_light_color ) },
            { "value", { "r", cmd.get_color( ).r }, { "g", cmd.get_color( ).g }, { "b", cmd.get_color( ).b } }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::curtains::open& cmd )
    {
        payload = {
            { "type", to_string( domain::enums::action_type::open_curtain ) }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::curtains::close& cmd )
    {
        payload = {
            { "type", to_string( domain::enums::action_type::close_curtain ) }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::curtains::set_position& cmd )
    {
        payload = {
            { "type",  to_string( domain::enums::action_type::set_curtain_position ) },
            { "value", cmd.get_position_value( )                                     }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::socket::turn_on& cmd )
    {
        payload = {
            { "type", to_string( domain::enums::action_type::turn_on_socket ) }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::socket::turn_off& cmd )
    {
        payload = {
            { "type", to_string( domain::enums::action_type::turn_off_socket ) }
        };
    }

    void mqtt_command_visitor::visit( const domain::rules::commands::thermostat::set_temperature& cmd )
    {
        payload = {
            { "type",  to_string( domain::enums::action_type::set_temperature ) },
            { "value", cmd.get_temperature( )                                   }
        };
    }

    std::string mqtt_command_visitor::get_payload( ) const
    {
        return payload.dump( );
    }

} // namespace rule_composer::core::util
