/**
 * \file turn_off.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/entities/device.hpp>
#include <domain/rules/commands/light/turn_off.hpp>

namespace rule_composer::domain::rules::commands::light
{
    bool turn_off::is_supported_by( entities::device& dev ) const
    {
        return dev.has_feature( enums::device_feature::switchable ) && ( enums::device_type::light == dev.get_type( ) );
    }
} // namespace rule_composer::domain::rules::commands::light
