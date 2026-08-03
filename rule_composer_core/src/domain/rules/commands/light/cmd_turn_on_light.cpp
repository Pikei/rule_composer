/**
 * \file cmd_turn_on_light.cpp
 * Created by Piotr Karol 2026
 */

#include <entities/device.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <rules/commands/light/cmd_turn_on_light.hpp>

namespace command::light
{
    bool cmd_turn_on_light::is_supported_by(device& dev) const
    {
        return dev.has_feature(device_feature::switchable) && (device_type::light == dev.get_type());
    }
} // command::light
