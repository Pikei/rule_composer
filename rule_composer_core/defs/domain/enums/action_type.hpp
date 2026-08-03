/**
 * \file action_type.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ACTION_TYPE_HPP
#define RULE_COMPOSER_ACTION_TYPE_HPP

#include <cstdint>

enum class light_action_t : std::uint8_t
{
    ON,
    OFF,
    BRIGHTNESS,
    RGB,
};

#endif // RULE_COMPOSER_ACTION_TYPE_HPP
