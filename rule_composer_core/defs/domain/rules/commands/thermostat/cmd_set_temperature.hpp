/**
 * \file cmd_set_temperature.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_SET_TEMPERATURE_HPP
#define RULE_COMPOSER_CMD_SET_TEMPERATURE_HPP

#include <rules/commands/command_interface.hpp>

namespace command::thermostat
{

    class cmd_set_temperature : public command_interface
    {
    public:
        bool is_supported_by(device& dev) const override;
    };

} // command::thermostat

#endif // RULE_COMPOSER_CMD_SET_TEMPERATURE_HPP
