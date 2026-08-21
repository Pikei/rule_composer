/**
 * \file set_position.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/entities/device.hpp>
#include <domain/rules/commands/curtains/set_position.hpp>

namespace rule_composer::domain::rules::commands::curtains
{
    set_position::set_position( std::uint8_t position ) : position( std::min( position, max_position ) )
    {
    }

    bool set_position::is_supported_by( entities::device& dev ) const
    {
        return dev.has_feature( enums::device_feature::position ) && ( enums::device_type::curtain == dev.get_type( ) );
    }

    std::uint8_t set_position::get_position_value( ) const
    {
        return position;
    }

} // namespace rule_composer::domain::rules::commands::curtains
