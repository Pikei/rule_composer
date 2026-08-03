/**
 * \file device_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_TYPE_HPP
#define RULE_COMPOSER_DEVICE_TYPE_HPP
#include <cstdint>

enum class device_type : std::uint8_t
{
    light,
    curtain,
    electric_socket,
    thermostat
};

inline const char* to_string(const device_type type)
{
    switch (type)
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

#endif // RULE_COMPOSER_DEVICE_TYPE_HPP
