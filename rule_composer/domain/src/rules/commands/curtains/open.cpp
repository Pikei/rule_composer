/**
 * \file open.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/entities/device.hpp>
#include <domain/rules/commands/curtains/open.hpp>

namespace rule_composer::domain::rules::commands::curtains
{
    bool open::is_supported_by( entities::device& dev ) const
    {
        return dev.has_feature( enums::device_feature::position ) && ( enums::device_type::curtain == dev.get_type( ) );
    }
} // namespace rule_composer::domain::rules::commands::curtains
