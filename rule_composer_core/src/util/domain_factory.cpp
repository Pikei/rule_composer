/**
 * \file domain_factory.cpp
 * Created by Piotr Karol 2026
 */

#include <entities/device.hpp>
#include <rules/commands/curtains/cmd_close_curtain.hpp>
#include <rules/commands/curtains/cmd_open_curtain.hpp>
#include <rules/commands/curtains/cmd_set_position.hpp>
#include <rules/commands/light/cmd_set_brightness.hpp>
#include <rules/commands/light/cmd_set_light_color.hpp>
#include <rules/commands/light/cmd_turn_off_light.hpp>
#include <rules/commands/light/cmd_turn_on_light.hpp>
#include <rules/commands/socket/cmd_turn_off_socket.hpp>
#include <rules/commands/socket/cmd_turn_on_socket.hpp>
#include <rules/commands/thermostat/cmd_set_temperature.hpp>
#include <rules/conditions/condition_group.hpp>
#include <util/domain_factory.hpp>

std::vector< room > domain_factory::create_rooms( const configuration_dto& dto )
{
    std::vector< room > result;
    for ( const auto& d : dto.rooms )
    {
        result.push_back( room { d.id, d.name } );
    }
    return result;
}

std::vector< group > domain_factory::create_groups( const configuration_dto& dto )
{
    std::vector< group > result;
    result.reserve( dto.groups.size( ) );
    for ( const auto& d : dto.groups )
    {
        result.push_back( group { d.id, d.name } );
    }
    return result;
}

std::vector< device > domain_factory::create_devices( const configuration_dto& dto )
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
    }
    return result;
}

rule domain_factory::create_rule( const rule_dto& dto )
{
    return rule { dto.id, create_condition( dto.condition ), create_commands( dto ) };
}

std::unique_ptr< condition_node > domain_factory::create_condition( const condition_dto& dto )
{
    if ( dto.children.empty( ) )
    {
        return std::make_unique< condition >( dto.type.value( ), dto.comp_op.value( ), dto.value.value( ) );
    }

    auto group = std::make_unique< condition_group >( dto.log_op.value( ) );
    for ( const auto& child : dto.children )
    {
        group->add( create_condition( child ) );
    }
    return group;
}

std::vector< std::unique_ptr< command_interface > > domain_factory::create_commands( const rule_dto& dto )
{
    std::vector< std::unique_ptr< command_interface > > result;
    result.reserve( dto.actions.size( ) );
    for ( const auto& d : dto.actions )
    {
        result.push_back( create_command( *d ) );
    }
    return result;
}

std::unique_ptr< command_interface > domain_factory::create_command( const command_dto& dto )
{
    switch ( dto.get_type( ) )
    {
        case action_type::turn_on_light:
            return std::make_unique< command::light::cmd_turn_on_light >( );
        case action_type::turn_off_light:
            return std::make_unique< command::light::cmd_turn_off_light >( );
        case action_type::set_brightness:
            return create_parametrised_command< command::light::cmd_set_brightness, std::uint8_t >( dto );
        case action_type::set_light_color:
            return create_parametrised_command< command::light::cmd_set_light_color, rgb_color >( dto );
        case action_type::turn_on_socket:
            return std::make_unique< command::socket::cmd_turn_on_socket >( );
        case action_type::turn_off_socket:
            return std::make_unique< command::socket::cmd_turn_off_socket >( );
        case action_type::open_curtain:
            return std::make_unique< command::curtain::cmd_open_curtain >( );
        case action_type::close_curtain:
            return std::make_unique< command::curtain::cmd_close_curtain >( );
        case action_type::set_curtain_position:
            return create_parametrised_command< command::curtain::cmd_set_position, std::uint8_t >( dto );
        case action_type::set_temperature:
            return create_parametrised_command< command::thermostat::cmd_set_temperature, double >( dto );
        default:
            return nullptr;
    }
}
