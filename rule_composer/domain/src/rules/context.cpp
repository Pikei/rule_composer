/**
 * \file context.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/context.hpp>

namespace rule_composer::domain::rules
{
    std::chrono::minutes context::get_current_time( ) const
    {
        const auto now = std::chrono::system_clock::now( );
        const auto tt  = std::chrono::system_clock::to_time_t( now );

        std::tm tm { };
        localtime_r( &tt, &tm );

        return std::chrono::hours { tm.tm_hour } + std::chrono::minutes { tm.tm_min };
    }

    enums::weekday context::get_weekday( ) const
    {
        const auto now        = std::chrono::system_clock::now( );
        const auto time_t_now = std::chrono::system_clock::to_time_t( now );
        const auto local_time = *std::localtime( &time_t_now );

        switch ( local_time.tm_wday )
        {
            case 0:
                return enums::weekday::sunday;
            case 1:
                return enums::weekday::monday;
            case 2:
                return enums::weekday::tuesday;
            case 3:
                return enums::weekday::wednesday;
            case 4:
                return enums::weekday::thursday;
            case 5:
                return enums::weekday::friday;
            case 6:
                return enums::weekday::saturday;
            default:
                return enums::weekday::unknown;
        }
    }

    double context::get_temperature( ) const
    {
        // TODO: Add temperature_sensor device type, and handle temperature updates.
        return 22; // Temporary default room temperature in Celsius
    }
} // namespace rule_composer::domain::rules
