/**
 * \file set_color.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/entities/device.hpp>
#include <domain/rules/commands/light/set_color.hpp>

namespace rule_composer::domain::rules::commands::light
{
    set_color::set_color( const rgb_color& color ) : color( color )
    {
    }

    rgb_color set_color::get_color( ) const
    {
        return color;
    }

    bool set_color::is_supported_by( entities::device& dev ) const
    {
        return dev.has_feature( enums::device_feature::rgb_control ) && ( enums::device_type::light == dev.get_type( ) );
    }
} // namespace rule_composer::domain::rules::commands::light
