/**
 * \file turn_on.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_TURN_ON_LIGHT_HPP
#define RULE_COMPOSER_CMD_TURN_ON_LIGHT_HPP

#include <domain/rules/commands/command_interface.hpp>

namespace rule_composer::domain::rules::commands::light
{
    class turn_on : public command_interface
    {
    public:

        bool is_supported_by( entities::device& dev ) const override;
    };

} // namespace rule_composer::domain::rules::commands::light

#endif // RULE_COMPOSER_CMD_TURN_ON_LIGHT_HPP
