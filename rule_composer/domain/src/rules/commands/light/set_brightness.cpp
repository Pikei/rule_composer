/**
 * \file set_brightness.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/entities/device.hpp>
#include <domain/rules/commands/light/set_brightness.hpp>

namespace rule_composer::domain::rules::commands::light
{
    set_brightness::set_brightness( const std::uint8_t brightness ) : brightness( brightness )
    {
    }

    bool set_brightness::is_supported_by( entities::device& dev ) const
    {
        return dev.has_feature( enums::device_feature::brightness ) && ( enums::device_type::light == dev.get_type( ) );
    }

    std::uint8_t set_brightness::get_brightness( ) const
    {
        return brightness;
    }
} // namespace rule_composer::domain::rules::commands::light
