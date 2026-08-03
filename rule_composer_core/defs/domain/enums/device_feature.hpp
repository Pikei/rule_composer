/**
 * \file device_feature.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_FEATURE_HPP
#define RULE_COMPOSER_DEVICE_FEATURE_HPP
#include <cstdint>

enum class device_feature : std::uint8_t
{
    switchable,
    brightness,
    rgb_control,
    position,
    temperature
};

inline const char* to_string(device_feature e)
{
    switch (e)
    {
    case device_feature::switchable:
        return "switchable";
    case device_feature::brightness:
        return "brightness";
    case device_feature::rgb_control:
        return "rgb_control";
    case device_feature::position:
        return "position";
    case device_feature::temperature:
        return "temperature";
    default:
        return "unknown";
    }
}

#endif // RULE_COMPOSER_DEVICE_FEATURE_HPP
