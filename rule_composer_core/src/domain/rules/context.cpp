/**
 * \file context.cpp
 * Created by Piotr Karol 2026
 */

#include <rules/context.hpp>

std::chrono::minutes context::get_current_time() const
{
    const auto time_point = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::minutes>(time_point.time_since_epoch());
}

weekday context::get_weekday() const
{
    const auto now        = std::chrono::system_clock::now();
    const auto time_t_now = std::chrono::system_clock::to_time_t(now);
    const auto local_time = *std::localtime(&time_t_now);

    switch (local_time.tm_wday)
    {
    case 0:
        return weekday::sunday;
    case 1:
        return weekday::monday;
    case 2:
        return weekday::tuesday;
    case 3:
        return weekday::wednesday;
    case 4:
        return weekday::thursday;
    case 5:
        return weekday::friday;
    case 6:
        return weekday::saturday;
    default:
        return weekday::unknown;
    }
}

double context::get_temperature() const
{
    // TODO: Add temperature_sensor device type, and handle temperature updates.
    return 22; // Temporary default room temperature in Celsius
}