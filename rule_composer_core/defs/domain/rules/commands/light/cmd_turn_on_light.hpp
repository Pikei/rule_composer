/**
 * \file cmd_turn_on_light.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_TURN_ON_LIGHT_HPP
#define RULE_COMPOSER_CMD_TURN_ON_LIGHT_HPP

#include <rules/commands/command_interface.hpp>

namespace command::light
{
    class cmd_turn_on_light : public command_interface
    {
    public:
        bool is_supported_by(device& dev) const override;
    };

} // command::light

#endif // RULE_COMPOSER_CMD_TURN_ON_LIGHT_HPP
