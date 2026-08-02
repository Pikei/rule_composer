/**
 * \file weekday.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_WEEKDAY_HPP
#define RULE_COMPOSER_WEEKDAY_HPP

#include <cstdint>

enum class weekday : std::uint8_t
{
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

inline const char* to_string(weekday day)
{
    switch (day)
    {
    case weekday::monday:
        return "monday";
    case weekday::tuesday:
        return "tuesday";
    case weekday::wednesday:
        return "wednesday";
    case weekday::thursday:
        return "thursday";
    case weekday::friday:
        return "friday";
    case weekday::saturday:
        return "saturday";
    case weekday::sunday:
        return "sunday";
    default:
        return "unknown";
    }
}

#endif // RULE_COMPOSER_WEEKDAY_HPP
