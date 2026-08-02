/**
 * \file abstract_device.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ABSTRACT_DEVICE_HPP
#define RULE_COMPOSER_ABSTRACT_DEVICE_HPP

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

class abstract_device
{
public:
    virtual ~abstract_device()  = default;
    virtual void execute_rule() = 0;
};

#endif // RULE_COMPOSER_ABSTRACT_DEVICE_HPP
