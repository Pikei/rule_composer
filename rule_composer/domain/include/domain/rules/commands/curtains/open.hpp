/**
 * \file open.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_OPEN_CURTAIN_HPP
#define RULE_COMPOSER_CMD_OPEN_CURTAIN_HPP

#include <domain/rules/commands/command_interface.hpp>

namespace rule_composer::domain::rules::commands::curtains
{
    class open : public command_interface
    {
    public:

        bool is_supported_by( entities::device& dev ) const override;
    };
} // namespace rule_composer::domain::rules::commands::curtains

#endif // RULE_COMPOSER_CMD_OPEN_CURTAIN_HPP
