/**
 * \file condition_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_TYPE_HPP
#define RULE_COMPOSER_CONDITION_TYPE_HPP

#include <cstdint>

enum class condition_type : std::uint8_t
{
    time,
    weekday,
    temperature,
};

inline const char* to_string(condition_type condition_t)
{
    switch (condition_t)
    {
    case condition_type::time:
        return "time";
    case condition_type::weekday:
        return "weekday";
    case condition_type::temperature:
        return "temperature";
    default:
        return "unknown";
    }
}

#endif // RULE_COMPOSER_CONDITION_TYPE_HPP
