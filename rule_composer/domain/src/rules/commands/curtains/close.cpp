/**
 * \file close.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/entities/device.hpp>
// #include <domain/enums/device_feature.hpp>
// #include <domain/enums/device_type.hpp>
#include <domain/rules/commands/curtains/close.hpp>

namespace rule_composer::domain::rules::commands::curtains
{
    bool close::is_supported_by( entities::device& dev ) const
    {
        return dev.has_feature( enums::device_feature::position ) && ( enums::device_type::curtain == dev.get_type( ) );
    }
} // namespace rule_composer::domain::rules::commands::curtains
