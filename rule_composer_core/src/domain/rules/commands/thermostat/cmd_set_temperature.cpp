/**
 * \file cmd_set_temperature.cpp
 * Created by Piotr Karol 2026
 */
#include <entities/device.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <rules/commands/thermostat/cmd_set_temperature.hpp>

namespace command::thermostat
{
    bool cmd_set_temperature::is_supported_by(device& dev) const
    {
        return dev.has_feature(device_feature::temperature) && (dev.get_type() == device_type::thermostat);
    }
} // command::thermostat
