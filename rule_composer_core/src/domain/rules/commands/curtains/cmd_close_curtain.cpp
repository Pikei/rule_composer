/**
 * \file cmd_close_curtain.cpp
 * Created by Piotr Karol 2026
 */
#include <entities/device.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <rules/commands/curtains/cmd_close_curtain.hpp>

namespace command::curtain
{
    bool cmd_close_curtain::is_supported_by( device& dev ) const
    {
        return dev.has_feature( device_feature::position ) && ( device_type::curtain == dev.get_type( ) );
    }
} // namespace command::curtain
