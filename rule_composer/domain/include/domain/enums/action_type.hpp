/**
 * \file action_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ACTION_TYPE_HPP
#define RULE_COMPOSER_ACTION_TYPE_HPP

#include <cstdint>
#include <string>

namespace rule_composer::domain::enums
{
    enum class action_type : std::uint8_t
    {
        unknown = 0,
        turn_on_light,
        turn_off_light,
        set_brightness,
        set_light_color,

        turn_on_socket,
        turn_off_socket,

        open_curtain,
        close_curtain,
        set_curtain_position,

        set_temperature,
    };
} // namespace rule_composer::domain::enums

inline const char* to_string( rule_composer::domain::enums::action_type e )
{
    switch ( e )
    {
        case rule_composer::domain::enums::action_type::turn_on_light:
            return "turn_on_light";
        case rule_composer::domain::enums::action_type::turn_off_light:
            return "turn_off_light";
        case rule_composer::domain::enums::action_type::set_brightness:
            return "set_brightness";
        case rule_composer::domain::enums::action_type::set_light_color:
            return "set_light_color";
        case rule_composer::domain::enums::action_type::turn_on_socket:
            return "turn_on_socket";
        case rule_composer::domain::enums::action_type::turn_off_socket:
            return "turn_off_socket";
        case rule_composer::domain::enums::action_type::open_curtain:
            return "open_curtain";
        case rule_composer::domain::enums::action_type::close_curtain:
            return "close_curtain";
        case rule_composer::domain::enums::action_type::set_curtain_position:
            return "set_curtain_position";
        case rule_composer::domain::enums::action_type::set_temperature:
            return "set_temperature";
        default:
            return "unknown";
    }
}

inline rule_composer::domain::enums::action_type str_to_action_type( const std::string& str )
{
    if ( to_string( rule_composer::domain::enums::action_type::turn_on_light ) == str )
    {
        return rule_composer::domain::enums::action_type::turn_on_light;
    }
    if ( to_string( rule_composer::domain::enums::action_type::turn_off_light ) == str )
    {
        return rule_composer::domain::enums::action_type::turn_off_light;
    }
    if ( to_string( rule_composer::domain::enums::action_type::set_brightness ) == str )
    {
        return rule_composer::domain::enums::action_type::set_brightness;
    }
    if ( to_string( rule_composer::domain::enums::action_type::set_light_color ) == str )
    {
        return rule_composer::domain::enums::action_type::set_light_color;
    }
    if ( to_string( rule_composer::domain::enums::action_type::turn_on_socket ) == str )
    {
        return rule_composer::domain::enums::action_type::turn_on_socket;
    }
    if ( to_string( rule_composer::domain::enums::action_type::turn_off_socket ) == str )
    {
        return rule_composer::domain::enums::action_type::turn_off_socket;
    }
    if ( to_string( rule_composer::domain::enums::action_type::open_curtain ) == str )
    {
        return rule_composer::domain::enums::action_type::open_curtain;
    }
    if ( to_string( rule_composer::domain::enums::action_type::close_curtain ) == str )
    {
        return rule_composer::domain::enums::action_type::close_curtain;
    }
    if ( to_string( rule_composer::domain::enums::action_type::set_curtain_position ) == str )
    {
        return rule_composer::domain::enums::action_type::set_curtain_position;
    }
    if ( to_string( rule_composer::domain::enums::action_type::set_temperature ) == str )
    {
        return rule_composer::domain::enums::action_type::set_temperature;
    }
    return rule_composer::domain::enums::action_type::unknown;
}

#endif // RULE_COMPOSER_ACTION_TYPE_HPP
