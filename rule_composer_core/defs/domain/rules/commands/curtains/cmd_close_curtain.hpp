/**
 * \file cmd_close_curtain.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_CLOSE_CURTAIN_HPP
#define RULE_COMPOSER_CMD_CLOSE_CURTAIN_HPP

#include <rules/commands/command_interface.hpp>

namespace command::curtain
{
    class cmd_close_curtain : public command_interface
    {
    public:

        bool is_supported_by( device& dev ) const override;
    };
} // namespace command::curtain

#endif // RULE_COMPOSER_CMD_CLOSE_CURTAIN_HPP
