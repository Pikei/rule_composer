/**
 * \file set_temperature.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_SET_TEMPERATURE_HPP
#define RULE_COMPOSER_CMD_SET_TEMPERATURE_HPP

#include <domain/rules/commands/command_interface.hpp>

namespace rule_composer::domain::rules::commands::thermostat
{

    class set_temperature : public command_interface
    {
    public:

        explicit set_temperature( double temperature );
        bool is_supported_by( entities::device& dev ) const override;

        [[nodiscard]]
        double get_temperature( ) const;

    private:

        double temperature;
    };

} // namespace rule_composer::domain::rules::commands::thermostat

#endif // RULE_COMPOSER_CMD_SET_TEMPERATURE_HPP
