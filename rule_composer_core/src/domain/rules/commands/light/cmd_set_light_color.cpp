/**
 * \file cmd_set_light_color.cpp
 * Created by Piotr Karol 2026
 */
#include <domain/rules/commands/light/cmd_set_light_color.hpp>
#include <entities/device.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>

namespace command::light
{
    cmd_set_light_color::cmd_set_light_color( const rgb_color& color ) : color( color )
    {
    }

    rgb_color cmd_set_light_color::get_color( ) const
    {
        return color;
    }

    bool cmd_set_light_color::is_supported_by( device& dev ) const
    {
        return dev.has_feature( device_feature::rgb_control ) && ( device_type::light == dev.get_type( ) );
    }
} // namespace command::light
