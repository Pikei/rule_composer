/**
 * \file device_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_TYPE_HPP
#define RULE_COMPOSER_DEVICE_TYPE_HPP
#include <cstdint>
#include <string>

enum class device_type : std::uint8_t
{
    unknown = 0,
    light,
    curtain,
    electric_socket,
    thermostat,
};

inline const char* to_string( const device_type type )
{
    switch ( type )
    {
        case device_type::light:
            return "light";
        case device_type::curtain:
            return "curtain";
        case device_type::electric_socket:
            return "electric_socket";
        case device_type::thermostat:
            return "thermostat";
        default:
            return "unknown";
    }
}

inline device_type str_to_device_type( const std::string& str )
{
    if ( str == to_string( device_type::light ) )
    {
        return device_type::light;
    }
    if ( str == to_string( device_type::curtain ) )
    {
        return device_type::curtain;
    }
    if ( str == to_string( device_type::electric_socket ) )
    {
        return device_type::electric_socket;
    }
    if ( str == to_string( device_type::thermostat ) )
    {
        return device_type::thermostat;
    }
    return device_type::unknown;
}

#endif // RULE_COMPOSER_DEVICE_TYPE_HPP
