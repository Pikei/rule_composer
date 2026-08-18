/**
 * \file device_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_TYPE_HPP
#define RULE_COMPOSER_DEVICE_TYPE_HPP

#include <cstdint>
#include <string>

namespace rule_composer::domain::enums
{
    enum class device_type : std::uint8_t
    {
        unknown = 0,
        light,
        curtain,
        electric_socket,
        thermostat,
    };
} // namespace rule_composer::domain::enums

inline const char* to_string( const rule_composer::domain::enums::device_type type )
{
    switch ( type )
    {
        case rule_composer::domain::enums::device_type::light:
            return "light";
        case rule_composer::domain::enums::device_type::curtain:
            return "curtain";
        case rule_composer::domain::enums::device_type::electric_socket:
            return "electric_socket";
        case rule_composer::domain::enums::device_type::thermostat:
            return "thermostat";
        default:
            return "unknown";
    }
}

inline rule_composer::domain::enums::device_type str_to_device_type( const std::string& str )
{
    if ( str == to_string( rule_composer::domain::enums::device_type::light ) )
    {
        return rule_composer::domain::enums::device_type::light;
    }
    if ( str == to_string( rule_composer::domain::enums::device_type::curtain ) )
    {
        return rule_composer::domain::enums::device_type::curtain;
    }
    if ( str == to_string( rule_composer::domain::enums::device_type::electric_socket ) )
    {
        return rule_composer::domain::enums::device_type::electric_socket;
    }
    if ( str == to_string( rule_composer::domain::enums::device_type::thermostat ) )
    {
        return rule_composer::domain::enums::device_type::thermostat;
    }
    return rule_composer::domain::enums::device_type::unknown;
}

#endif // RULE_COMPOSER_DEVICE_TYPE_HPP
