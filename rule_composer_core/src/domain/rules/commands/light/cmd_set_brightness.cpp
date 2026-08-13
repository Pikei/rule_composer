/**
 * \file cmd_set_brightness.cpp
 * Created by Piotr Karol 2026
 */
#include <entities/device.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <rules/commands/light/cmd_set_brightness.hpp>

namespace command::light
{
    cmd_set_brightness::cmd_set_brightness( std::uint8_t brightness ) : brightness( brightness )
    {
    }

    bool cmd_set_brightness::is_supported_by( device& dev ) const
    {
        return dev.has_feature( device_feature::brightness ) && ( device_type::light == dev.get_type( ) );
    }

    std::uint8_t cmd_set_brightness::get_brightness( ) const
    {
        return brightness;
    }
} // namespace command::light
