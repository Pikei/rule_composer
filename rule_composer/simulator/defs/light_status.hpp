/**
 * \file light_status.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LIGHT_STATUS_HPP
#define RULE_COMPOSER_LIGHT_STATUS_HPP
#include <optional>

#include "domain/rules/commands/light/set_color.hpp"

namespace rule_composer::simulator
{
    using namespace domain::rules::commands::light;
    struct light_status
    {
        bool                          on = false;
        std::optional< std::uint8_t > brightness;
        std::optional< rgb_color >    color;
    };
} // namespace rule_composer::simulator

#endif // RULE_COMPOSER_LIGHT_STATUS_HPP
