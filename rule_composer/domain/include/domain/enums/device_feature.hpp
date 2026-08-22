/**
 * \file device_feature.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_FEATURE_HPP
#define RULE_COMPOSER_DEVICE_FEATURE_HPP

#include <cstdint>
#include <string>

namespace rule_composer::domain::enums
{
    enum class device_feature : std::uint8_t
    {
        unknown = 0,
        switchable,
        brightness,
        rgb_control,
        position,
        temperature_control,
        temperature_measurement,
        humidity_measurement,
    };
} // namespace rule_composer::domain::enums

inline const char* to_string( rule_composer::domain::enums::device_feature e )
{
    switch ( e )
    {
        case rule_composer::domain::enums::device_feature::switchable:
            return "switchable";
        case rule_composer::domain::enums::device_feature::brightness:
            return "brightness";
        case rule_composer::domain::enums::device_feature::rgb_control:
            return "rgb_control";
        case rule_composer::domain::enums::device_feature::position:
            return "position";
        case rule_composer::domain::enums::device_feature::temperature_control:
            return "temperature";
        case rule_composer::domain::enums::device_feature::temperature_measurement:
            return "temperature_measurement";
        case rule_composer::domain::enums::device_feature::humidity_measurement:
            return "humidity_measurement";
        default:
            return "unknown";
    }
}

inline rule_composer::domain::enums::device_feature str_to_device_feature( const std::string& str )
{
    if ( to_string( rule_composer::domain::enums::device_feature::switchable ) == str )
    {
        return rule_composer::domain::enums::device_feature::switchable;
    }
    if ( to_string( rule_composer::domain::enums::device_feature::brightness ) == str )
    {
        return rule_composer::domain::enums::device_feature::brightness;
    }
    if ( to_string( rule_composer::domain::enums::device_feature::rgb_control ) == str )
    {
        return rule_composer::domain::enums::device_feature::rgb_control;
    }
    if ( to_string( rule_composer::domain::enums::device_feature::position ) == str )
    {
        return rule_composer::domain::enums::device_feature::position;
    }
    if ( to_string( rule_composer::domain::enums::device_feature::temperature_control ) == str )
    {
        return rule_composer::domain::enums::device_feature::temperature_control;
    }
    if ( to_string( rule_composer::domain::enums::device_feature::temperature_measurement ) == str )
    {
        return rule_composer::domain::enums::device_feature::temperature_measurement;
    }
    if ( to_string( rule_composer::domain::enums::device_feature::humidity_measurement ) == str )
    {
        return rule_composer::domain::enums::device_feature::humidity_measurement;
    }
    return rule_composer::domain::enums::device_feature::unknown;
}

#endif // RULE_COMPOSER_DEVICE_FEATURE_HPP
