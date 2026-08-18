/**
 * \file condition_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_TYPE_HPP
#define RULE_COMPOSER_CONDITION_TYPE_HPP

#include <cstdint>
#include <string>

namespace rule_composer::domain::enums
{
    enum class condition_type : std::uint8_t
    {
        unknown = 0,
        time,
        weekday,
        temperature,
    };
} // namespace rule_composer::domain::enums

inline const char* to_string( rule_composer::domain::enums::condition_type condition_t )
{
    switch ( condition_t )
    {
        case rule_composer::domain::enums::condition_type::time:
            return "time";
        case rule_composer::domain::enums::condition_type::weekday:
            return "weekday";
        case rule_composer::domain::enums::condition_type::temperature:
            return "temperature";
        default:
            return "unknown";
    }
}

inline rule_composer::domain::enums::condition_type str_to_condition_type( const std::string& str )
{
    if ( to_string( rule_composer::domain::enums::condition_type::time ) == str )
    {
        return rule_composer::domain::enums::condition_type::time;
    }
    if ( to_string( rule_composer::domain::enums::condition_type::weekday ) == str )
    {
        return rule_composer::domain::enums::condition_type::weekday;
    }
    if ( to_string( rule_composer::domain::enums::condition_type::temperature ) == str )
    {
        return rule_composer::domain::enums::condition_type::temperature;
    }
    return rule_composer::domain::enums::condition_type::unknown;
}

#endif // RULE_COMPOSER_CONDITION_TYPE_HPP
