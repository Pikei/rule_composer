/**
 * \file cmd_open_curtain.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_OPEN_CURTAIN_HPP
#define RULE_COMPOSER_CMD_OPEN_CURTAIN_HPP

#include <rules/commands/command_interface.hpp>

namespace command::curtain
{
    class cmd_open_curtain : public command_interface
    {
    public:
        bool is_supported_by(device& dev) const override;
    };
} // command::curtain

#endif // RULE_COMPOSER_CMD_OPEN_CURTAIN_HPP
