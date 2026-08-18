/**
 * \file domain_factory.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/entities/device.hpp>
#include <domain/rules/commands/curtains/close.hpp>
#include <domain/rules/commands/curtains/open.hpp>
#include <domain/rules/commands/curtains/set_position.hpp>
#include <domain/rules/commands/light/set_brightness.hpp>
#include <domain/rules/commands/light/set_color.hpp>
#include <domain/rules/commands/light/turn_off.hpp>
#include <domain/rules/commands/light/turn_on.hpp>
#include <domain/rules/commands/socket/turn_off.hpp>
#include <domain/rules/commands/socket/turn_on.hpp>
#include <domain/rules/commands/thermostat/set_temperature.hpp>
#include <domain/rules/conditions/condition_group.hpp>
#include <util/domain_factory.hpp>

namespace rule_composer::core::util
{
    using namespace domain::enums;
    using namespace domain::rules;
    using namespace domain::entities;

    std::vector< room > domain_factory::create_rooms( const dto::configuration_dto& dto )
    {
        std::vector< room > result;
        for ( const auto& d : dto.rooms )
        {
            result.push_back( room { d.id, d.name } );
        }
        return result;
    }

    std::vector< group > domain_factory::create_groups( const dto::configuration_dto& dto )
    {
        std::vector< group > result;
        result.reserve( dto.groups.size( ) );
        for ( const auto& d : dto.groups )
        {
            result.push_back( group { d.id, d.name } );
        }
        return result;
    }

    std::vector< device > domain_factory::create_devices( const dto::configuration_dto& dto )
    {
        std::vector< device > result;
        result.reserve( dto.devices.size( ) );
        for ( const auto& d : dto.devices )
        {
            device dev { d.id, d.name, d.type, d.room, d.group };
            for ( const auto& r : d.rules )
            {
                dev.add_rule( create_rule( r ) );
            }
            result.push_back( std::move( dev ) ); // <-- tego brakuje
        }
        return result;
    }

    rule domain_factory::create_rule( const dto::rule_dto& dto )
    {
        return rule { dto.id, create_condition( dto.condition ), create_commands( dto ) };
    }

    std::unique_ptr< conditions::condition_node > domain_factory::create_condition( const dto::condition_dto& dto )
    {
        if ( dto.children.empty( ) )
        {
            return std::make_unique< conditions::condition >( dto.type.value( ), dto.comp_op.value( ), dto.value.value( ) );
        }

        auto group = std::make_unique< conditions::condition_group >( dto.log_op.value( ) );
        for ( const auto& child : dto.children )
        {
            group->add( create_condition( child ) );
        }
        return group;
    }

    std::vector< std::unique_ptr< command_interface > > domain_factory::create_commands( const dto::rule_dto& dto )
    {
        std::vector< std::unique_ptr< command_interface > > result;
        result.reserve( dto.actions.size( ) );
        for ( const auto& d : dto.actions )
        {
            result.push_back( create_command( *d ) );
        }
        return result;
    }

    std::unique_ptr< command_interface > domain_factory::create_command( const dto::command_dto& dto )
    {
        switch ( dto.get_type( ) )
        {
            case action_type::turn_on_light:
                return std::make_unique< commands::light::turn_on >( );
            case action_type::turn_off_light:
                return std::make_unique< commands::light::turn_off >( );
            case action_type::set_brightness:
                return create_parametrised_command< commands::light::set_brightness, std::uint8_t >( dto );
            case action_type::set_light_color:
                return create_parametrised_command< commands::light::set_color, commands::light::rgb_color >( dto );
            case action_type::turn_on_socket:
                return std::make_unique< commands::socket::turn_on >( );
            case action_type::turn_off_socket:
                return std::make_unique< commands::socket::turn_off >( );
            case action_type::open_curtain:
                return std::make_unique< commands::curtains::open >( );
            case action_type::close_curtain:
                return std::make_unique< commands::curtains::close >( );
            case action_type::set_curtain_position:
                return create_parametrised_command< commands::curtains::set_position, std::uint8_t >( dto );
            case action_type::set_temperature:
                return create_parametrised_command< commands::thermostat::set_temperature, double >( dto );
            default:
                return nullptr;
        }
    }
} // namespace rule_composer::core::util
