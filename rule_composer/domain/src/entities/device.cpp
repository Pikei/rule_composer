/**
 * \file device.cpp
 * Created by Piotr Karol 2026
 */

#include <algorithm>
#include <utility>

#include <domain/entities/device.hpp>

namespace rule_composer::domain::entities
{
    device::device( id_types::device_id id, std::string name, enums::device_type type, id_types::room_id room, std::optional< id_types::group_id > group ) :
        id { id },
        name { std::move( name ) },
        type { type },
        room { room }
    {
        if ( group.has_value( ) )
        {
            this->group = group.value( );
        }
    }

    void device::add_rule( rules::rule new_rule )
    {
        for ( const auto& action : new_rule )
        {
            if ( !action->is_supported_by( *this ) )
            {
                return;
            }
        }

        rules.push_back( std::move( new_rule ) );
    }

    id_types::device_id device::get_id( ) const
    {
        return id;
    }

    const std::string& device::get_name( ) const
    {
        return name;
    }

    enums::device_type device::get_type( ) const
    {
        return type;
    }

    id_types::room_id device::get_room_id( ) const
    {
        return room;
    }

    std::optional< id_types::group_id > device::get_group( ) const
    {
        return group;
    }

    const std::vector< rules::rule >& device::get_rules( ) const
    {
        return rules;
    }

    const std::vector< enums::device_feature >& device::get_features( ) const
    {
        return features;
    }

    bool device::has_feature( enums::device_feature feature )
    {
        return std::any_of( features.begin( ), features.end( ), [feature]( const auto& f ) { return f == feature; } );
    }
} // namespace rule_composer::domain::entities
