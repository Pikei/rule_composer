/**
 * \file set_temperature.cpp
 * Created by Piotr Karol 2026
 */
#include <domain/entities/device.hpp>
#include <domain/rules/commands/thermostat/set_temperature.hpp>

namespace rule_composer::domain::rules::commands::thermostat
{
    set_temperature::set_temperature( double temperature ) : temperature( temperature )
    {
    }

    bool set_temperature::is_supported_by( entities::device& dev ) const
    {
        return dev.has_feature( enums::device_feature::temperature_control ) && ( dev.get_type( ) == enums::device_type::thermostat );
    }

    double set_temperature::get_temperature( ) const
    {
        return temperature;
    }
} // namespace rule_composer::domain::rules::commands::thermostat
