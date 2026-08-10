/**
 * \file weekday.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_WEEKDAY_HPP
#define RULE_COMPOSER_WEEKDAY_HPP

#include <cstdint>

enum class weekday : std::uint8_t
{
    unknown = 0,
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

inline weekday str_to_weekday(const std::string& str)
{
    if (to_string(weekday::monday) == str)
    {
        return weekday::monday;
    }
    if (to_string(weekday::tuesday) == str)
    {
        return weekday::tuesday;
    }
    if (to_string(weekday::wednesday) == str)
    {
        return weekday::wednesday;
    }
    if (to_string(weekday::thursday) == str)
    {
        return weekday::thursday;
    }
    if (to_string(weekday::friday) == str)
    {
        return weekday::friday;
    }
    if (to_string(weekday::saturday) == str)
    {
        return weekday::saturday;
    }
    if (to_string(weekday::sunday) == str)
    {
        return weekday::sunday;
    }
    return weekday::unknown;
}

#endif // RULE_COMPOSER_WEEKDAY_HPP
