/**
 * \file cmd_turn_off_light.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_TURN_OFF_LIGHT_HPP
#define RULE_COMPOSER_CMD_TURN_OFF_LIGHT_HPP

#include <rules/commands/command_interface.hpp>

namespace command::light
{
    class cmd_turn_off_light : public command_interface
    {
    public:
        bool is_supported_by(device& dev) const override;
    };
}

#endif // RULE_COMPOSER_CMD_TURN_OFF_LIGHT_HPP
