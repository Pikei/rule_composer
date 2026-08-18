/**
 * \file config_parser.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/enums/action_type.hpp>
#include <domain/enums/comparison_operator.hpp>
#include <domain/enums/condition_type.hpp>
#include <domain/enums/device_type.hpp>
#include <domain/enums/logical_operator.hpp>
#include <domain/enums/weekday.hpp>
#include <domain/rules/commands/light/set_color.hpp>
#include <util/config_parser.hpp>

namespace rule_composer::core::util
{
    using namespace domain::enums;

    config_parser::config_parser( const std::shared_ptr< spdlog::logger >& logger_ ) : json_utils( logger_ )
    {
    }

    config_parser::config_parser( const std::string& file_path_, const std::shared_ptr< spdlog::logger >& logger_ ) : json_utils( file_path_, logger_ )
    {
    }

    dto::configuration_dto config_parser::parse_config( const std::string& file_path_ )
    {
        logger->info( "Loading configuration..." );
        logger->debug( "[1/4] Loading config file..." );
        load_file( file_path_ );
        logger->debug( "[2/4] Loading rooms configuration..." );
        dto::configuration_dto config;
        parse_rooms( config );
        logger->debug( "[3/4] Loading groups configuration..." );
        parse_groups( config );
        logger->debug( "[4/4] Loading devices configuration..." );
        parse_devices( config );
        logger->info( "Configuration loaded successfully." );
        return config;
    }

    dto::configuration_dto config_parser::parse_config( )
    {
        return parse_config( default_file_path );
    }

    void config_parser::parse_rooms( dto::configuration_dto& config )
    {
        for ( std::size_t i = 0; i < document.at( "rooms" ).size( ); ++i )
        {
            dto::room_dto room;
            room.id   = get_value< domain::id_types::room_id >( fmt::format( "rooms[{}].id", i ) );
            room.name = get_value< std::string >( fmt::format( "rooms[{}].name", i ) );
            config.rooms.push_back( room );
        }
    }
    void config_parser::parse_groups( dto::configuration_dto& config )
    {
        for ( std::size_t i = 0; i < document.at( "groups" ).size( ); ++i )
        {
            dto::group_dto group;
            group.id   = get_value< domain::id_types::room_id >( fmt::format( "groups[{}].id", i ) );
            group.name = get_value< std::string >( fmt::format( "groups[{}].name", i ) );
            config.groups.push_back( group );
        }
    }

    void config_parser::parse_devices( dto::configuration_dto& config )
    {
        for ( std::size_t i = 0; i < document.at( "devices" ).size( ); ++i )
        {
            dto::device_dto device { };
            device.id    = get_value< domain::id_types::room_id >( fmt::format( "devices[{}].id", i ) );
            device.name  = get_value< std::string >( fmt::format( "devices[{}].name", i ) );
            device.type  = str_to_device_type( get_value< std::string >( fmt::format( "devices[{}].type", i ) ) );
            device.group = get_optional< domain::id_types::group_id >( fmt::format( "devices[{}].group", i ) );
            device.room  = get_value< domain::id_types::room_id >( fmt::format( "devices[{}].room", i ) );
            parse_rules( device, i );
            config.devices.push_back( device );
        }
    }

    void config_parser::parse_rules( dto::device_dto& device, std::size_t device_index )
    {
        for ( std::size_t i = 0; i < document.at( "devices" ).at( device_index ).at( "rules" ).size( ); ++i )
        {
            const auto    rule_path = fmt::format( "devices[{}].rules[{}]", device_index, i );
            dto::rule_dto rule;
            rule.id = get_value< domain::id_types::rule_id >( fmt::format( "{}.id", rule_path ) );
            parse_expression( rule.condition, fmt::format( "{}.expression", rule_path ) );
            parse_actions( rule, rule_path );
            device.rules.push_back( rule );
        }
    }

    void config_parser::parse_expression( dto::condition_dto& condition, const std::string& exp_path )
    {
        const auto op = get_optional< std::string >( fmt::format( "{}.op", exp_path ) );
        if ( op == std::nullopt )
        {
            parse_simple_expression( condition, exp_path );
        }
        else
        {
            condition.log_op = str_to_logical_operator( op.value( ) );
            parse_compound_expression( condition, exp_path );
        }
    }

    void config_parser::parse_simple_expression( dto::condition_dto& condition, const std::string& exp_path )
    {
        condition.type    = str_to_condition_type( get_value< std::string >( fmt::format( "{}.type", exp_path ) ) );
        condition.comp_op = str_to_comparison_operator( get_value< std::string >( fmt::format( "{}.comparison", exp_path ) ) );
        if ( condition_type::time == condition.type )
        {
            condition.value = std::chrono::minutes { get_value< std::uint16_t >( fmt::format( "{}.value", exp_path ) ) };
        }
        else if ( condition_type::weekday == condition.type )
        {
            condition.value = str_to_weekday( get_value< std::string >( fmt::format( "{}.value", exp_path ) ) );
        }
        else if ( condition_type::temperature == condition.type )
        {
            condition.value = get_value< double >( fmt::format( "{}.value", exp_path ) );
        }
    }

    void config_parser::parse_compound_expression( dto::condition_dto& condition, const std::string& exp_path )
    {
        const auto children_node = navigate( fmt::format( "{}.children", exp_path ) );
        for ( std::size_t i = 0; i < children_node->size( ); ++i )
        {
            dto::condition_dto child_condition;
            parse_expression( child_condition, fmt::format( "{}.children[{}]", exp_path, i ) );
            condition.children.push_back( child_condition );
        }
    }

    void config_parser::parse_actions( dto::rule_dto& rule, const std::string& rule_path )
    {
        const auto actions_node = navigate( fmt::format( "{}.actions", rule_path ) );
        for ( std::size_t i = 0; i < actions_node->size( ); ++i )
        {
            action_type type = str_to_action_type( get_value< std::string >( fmt::format( "{}.actions[{}].type", rule_path, i ) ) );
            rule.actions.push_back( parse_action( type, fmt::format( "{}.actions[{}]", rule_path, i ) ) );
        }
    }

    std::shared_ptr< dto::command_dto > config_parser::parse_action( action_type type, const std::string& action_path )
    {
        std::string value_path = fmt::format( "{}.value", action_path );
        switch ( type )
        {
            case action_type::turn_on_light:
            case action_type::turn_off_light:
            case action_type::turn_on_socket:
            case action_type::turn_off_socket:
            case action_type::open_curtain:
            case action_type::close_curtain:
                return std::make_shared< dto::command_dto >( type );
            case action_type::set_brightness:
            case action_type::set_curtain_position:
                return std::make_shared< dto::parametrised_command_dto< std::uint8_t > >( type, get_value< std::uint8_t >( value_path ) );
            case action_type::set_temperature:
                return std::make_shared< dto::parametrised_command_dto< double > >( type, get_value< double >( value_path ) );
            case action_type::set_light_color:
                return parse_action_set_light_color( type, value_path );

            default:
                return nullptr;
        }
    }

    std::shared_ptr< dto::command_dto > config_parser::parse_action_set_light_color( action_type type, const std::string& value_path )
    {
        using namespace domain::rules::commands::light;
        const auto red   = get_value< std::uint8_t >( fmt::format( "{}.red", value_path ) );
        const auto green = get_value< std::uint8_t >( fmt::format( "{}.green", value_path ) );
        const auto blue  = get_value< std::uint8_t >( fmt::format( "{}.blue", value_path ) );
        return std::make_shared< dto::parametrised_command_dto< rgb_color > >( type, rgb_color { red, green, blue } );
    }
} // namespace rule_composer::core::util
