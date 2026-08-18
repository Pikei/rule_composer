/**
 * \file weekday.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_WEEKDAY_HPP
#define RULE_COMPOSER_WEEKDAY_HPP

#include <cstdint>
#include <string>

namespace rule_composer::domain::enums
{
    enum class weekday : std::uint8_t
    {
        unknown = 0,
        monday,
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday,
        sunday,
    };
} // namespace rule_composer::domain::enums

inline const char* to_string( rule_composer::domain::enums::weekday day )
{
    switch ( day )
    {
        case rule_composer::domain::enums::weekday::monday:
            return "monday";
        case rule_composer::domain::enums::weekday::tuesday:
            return "tuesday";
        case rule_composer::domain::enums::weekday::wednesday:
            return "wednesday";
        case rule_composer::domain::enums::weekday::thursday:
            return "thursday";
        case rule_composer::domain::enums::weekday::friday:
            return "friday";
        case rule_composer::domain::enums::weekday::saturday:
            return "saturday";
        case rule_composer::domain::enums::weekday::sunday:
            return "sunday";
        default:
            return "unknown";
    }
}

inline rule_composer::domain::enums::weekday str_to_weekday( const std::string& str )
{
    if ( to_string( rule_composer::domain::enums::weekday::monday ) == str )
    {
        return rule_composer::domain::enums::weekday::monday;
    }
    if ( to_string( rule_composer::domain::enums::weekday::tuesday ) == str )
    {
        return rule_composer::domain::enums::weekday::tuesday;
    }
    if ( to_string( rule_composer::domain::enums::weekday::wednesday ) == str )
    {
        return rule_composer::domain::enums::weekday::wednesday;
    }
    if ( to_string( rule_composer::domain::enums::weekday::thursday ) == str )
    {
        return rule_composer::domain::enums::weekday::thursday;
    }
    if ( to_string( rule_composer::domain::enums::weekday::friday ) == str )
    {
        return rule_composer::domain::enums::weekday::friday;
    }
    if ( to_string( rule_composer::domain::enums::weekday::saturday ) == str )
    {
        return rule_composer::domain::enums::weekday::saturday;
    }
    if ( to_string( rule_composer::domain::enums::weekday::sunday ) == str )
    {
        return rule_composer::domain::enums::weekday::sunday;
    }
    return rule_composer::domain::enums::weekday::unknown;
}

#endif // RULE_COMPOSER_WEEKDAY_HPP
