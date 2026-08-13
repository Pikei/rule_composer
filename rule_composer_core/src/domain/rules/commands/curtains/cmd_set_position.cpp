/**
 * \file cmd_set_position.cpp
 * Created by Piotr Karol 2026
 */

#include <entities/device.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <rules/commands/curtains/cmd_set_position.hpp>

namespace command::curtain
{
    cmd_set_position::cmd_set_position( std::uint8_t position ) : position( std::min( position, max_position ) )
    {
    }

    bool cmd_set_position::is_supported_by( device& dev ) const
    {
        return dev.has_feature( device_feature::position ) && ( device_type::curtain == dev.get_type( ) );
    }

} // namespace command::curtain
