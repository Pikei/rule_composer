/**
 * \file condition_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_TYPE_HPP
#define RULE_COMPOSER_CONDITION_TYPE_HPP

#include <cstdint>

enum class condition_type : std::uint8_t
{
    unknown = 0,
    time,
    weekday,
    temperature,
};

inline const char* to_string( condition_type condition_t )
{
    switch ( condition_t )
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

inline condition_type str_to_condition_type( const std::string& str )
{
    if ( to_string( condition_type::time ) == str )
    {
        return condition_type::time;
    }
    if ( to_string( condition_type::weekday ) == str )
    {
        return condition_type::weekday;
    }
    if ( to_string( condition_type::temperature ) == str )
    {
        return condition_type::temperature;
    }
    return condition_type::unknown;
}

#endif // RULE_COMPOSER_CONDITION_TYPE_HPP
