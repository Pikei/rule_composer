/**
 * \file config_parser.cpp
 * Created by Piotr Karol 2026
 */

#include "rules/commands/light/cmd_set_light_color.hpp"

#include <util/config_parser.hpp>

config_parser::config_parser(const logger_t& logger_) : json_utils(logger_)
{
}

config_parser::config_parser(const std::string& file_path_, const logger_t& logger_) : json_utils(file_path_, logger_)
{
}

configuration_dto config_parser::parse_config(const std::string& file_path_)
{
    logger->info("Loading configuration...");
    logger->debug("[1/4] Loading config file...");
    load_file(file_path_);
    logger->debug("[2/4] Loading rooms configuration...");
    configuration_dto config;
    parse_rooms(config);
    logger->debug("[3/4] Loading groups configuration...");
    parse_groups(config);
    logger->debug("[4/4] Loading devices configuration...");
    parse_devices(config);
    logger->info("Configuration loaded successfully.");
    return config;
}

configuration_dto config_parser::parse_config()
{
    return parse_config(default_file_path);
}

void config_parser::parse_rooms(configuration_dto& config)
{
    for (std::size_t i = 0; i < document.at("rooms").size(); ++i)
    {
        room_dto room;
        room.id   = get_value<room_id>(fmt::format("rooms[{}].id", i));
        room.name = get_value<std::string>(fmt::format("rooms[{}].name", i));
        config.rooms.push_back(room);
    }
}
void config_parser::parse_groups(configuration_dto& config)
{
    for (std::size_t i = 0; i < document.at("groups").size(); ++i)
    {
        group_dto group;
        group.id   = get_value<room_id>(fmt::format("groups[{}].id", i));
        group.name = get_value<std::string>(fmt::format("groups[{}].name", i));
        config.groups.push_back(group);
    }
}

void config_parser::parse_devices(configuration_dto& config)
{
    for (std::size_t i = 0; i < document.at("devices").size(); ++i)
    {
        device_dto device { };
        device.id    = get_value<room_id>(fmt::format("devices[{}].id", i));
        device.name  = get_value<std::string>(fmt::format("devices[{}].name", i));
        device.type  = str_to_device_type(get_value<std::string>(fmt::format("devices[{}].type", i)));
        device.group = get_optional<group_id>(fmt::format("devices[{}].group", i));
        device.room  = get_value<room_id>(fmt::format("devices[{}].room", i));
        parse_rules(device, i);
        config.devices.push_back(device);
    }
}

void config_parser::parse_rules(device_dto& device, std::size_t device_index)
{
    for (std::size_t i = 0; i < document.at("devices").at(device_index).at("rules").size(); ++i)
    {
        const auto rule_path = fmt::format("devices[{}].rules[{}]", device_index, i);
        rule_dto   rule;
        rule.id = get_value<rule_id>(fmt::format("{}.id", rule_path));
        condition_dto condition;
        parse_expression(condition, fmt::format("{}.expression", rule_path));
        parse_actions(rule, rule_path);
        device.rules.push_back(rule);
    }
}

void config_parser::parse_expression(condition_dto& condition, const std::string& exp_path)
{
    const auto op = get_optional<std::string>(fmt::format("{}.op", exp_path));
    if (op == std::nullopt)
    {
        parse_simple_expression(condition, exp_path);
    }
    else
    {
        condition.log_op = str_to_logical_operator(op.value());
        parse_compound_expression(condition, exp_path);
    }
}

void config_parser::parse_simple_expression(condition_dto& condition, const std::string& exp_path)
{
    condition.type    = str_to_condition_type(get_value<std::string>(fmt::format("{}.type", exp_path)));
    condition.comp_op = str_to_comparison_operator(get_value<std::string>(fmt::format("{}.comparison", exp_path)));
    if (condition_type::time == condition.type)
    {
        condition.value = std::chrono::minutes { get_value<std::uint16_t>(fmt::format("{}.value", exp_path)) };
    }
    else if (condition_type::weekday == condition.type)
    {
        condition.value = str_to_weekday(get_value<std::string>(fmt::format("{}.value", exp_path)));
    }
    else if (condition_type::temperature == condition.type)
    {
        condition.value = get_value<double>(fmt::format("{}.value", exp_path));
    }
}

void config_parser::parse_compound_expression(condition_dto& condition, const std::string& exp_path)
{
    const auto children_node = navigate(fmt::format("{}.children", exp_path));
    for (std::size_t i = 0; i < children_node->size(); ++i)
    {
        condition_dto child_condition;
        parse_expression(child_condition, fmt::format("{}.children[{}]", exp_path, i));
        condition.children.push_back(child_condition);
    }
}

void config_parser::parse_actions(rule_dto& rule, const std::string& rule_path)
{
    const auto actions_node = navigate(fmt::format("{}.actions", rule_path));
    for (std::size_t i = 0; i < actions_node->size(); ++i)
    {
        action_type type = str_to_action_type(get_value<std::string>(fmt::format("{}.actions[{}].type", rule_path, i)));
        rule.actions.push_back(parse_action(type, fmt::format("{}.actions[{}]", rule_path, i)));
    }
}

std::shared_ptr<command_dto> config_parser::parse_action(action_type type, const std::string& action_path)
{
    std::string value_path = fmt::format("{}.value", action_path);
    switch (type)
    {
    case action_type::turn_on_light:
        return parse_action_turn_on_light(type, value_path);
    case action_type::turn_off_light:
        return parse_action_turn_off_light(type, value_path);
    case action_type::set_brightness:
        return parse_action_set_brightness(type, value_path);
    case action_type::set_light_color:
        return parse_action_set_light_color(type, value_path);
    case action_type::turn_on_socket:
        return parse_action_turn_on_socket(type, value_path);
    case action_type::turn_off_socket:
        return parse_action_turn_off_socket(type, value_path);
    case action_type::open_curtain:
        return parse_action_open_curtain(type, value_path);
    case action_type::close_curtain:
        return parse_action_close_curtain(type, value_path);
    case action_type::set_curtain_position:
        return parse_action_set_curtain_position(type, value_path);
    case action_type::set_temperature:
        return parse_action_set_temperature(type, value_path);
    default:
        return nullptr;
    }
}

std::shared_ptr<command_dto> config_parser::parse_action_turn_on_light(action_type type, const std::string& value_path)
{
    return std::make_shared<command_dto>(type);
}

std::shared_ptr<command_dto> config_parser::parse_action_turn_off_light(action_type type, const std::string& value_path)
{
    return std::make_shared<command_dto>(type);
}

std::shared_ptr<command_dto> config_parser::parse_action_set_brightness(action_type type, const std::string& value_path)
{
    return std::make_shared<parametrised_command_dto<std::uint8_t>>(type, get_value<std::uint8_t>(value_path));
}

std::shared_ptr<command_dto> config_parser::parse_action_set_light_color(action_type type, const std::string& value_path)
{
    const auto red   = get_value<std::uint8_t>(fmt::format("{}.red", value_path));
    const auto green = get_value<std::uint8_t>(fmt::format("{}.green", value_path));
    const auto blue  = get_value<std::uint8_t>(fmt::format("{}.blue", value_path));
    return std::make_shared<parametrised_command_dto<rgb_color>>(type, rgb_color { red, green, blue });
}

std::shared_ptr<command_dto> config_parser::parse_action_turn_on_socket(action_type type, const std::string& value_path)
{
    return std::make_shared<command_dto>(type);
}

std::shared_ptr<command_dto> config_parser::parse_action_turn_off_socket(action_type type, const std::string& value_path)
{
    return std::make_shared<command_dto>(type);
}

std::shared_ptr<command_dto> config_parser::parse_action_open_curtain(action_type type, const std::string& value_path)
{
    return std::make_shared<command_dto>(type);
}

std::shared_ptr<command_dto> config_parser::parse_action_close_curtain(action_type type, const std::string& value_path)
{
    return std::make_shared<command_dto>(type);
}

std::shared_ptr<command_dto> config_parser::parse_action_set_curtain_position(action_type type, const std::string& value_path)
{
    return std::make_shared<parametrised_command_dto<std::uint8_t>>(type, get_value<std::uint8_t>(value_path));
}

std::shared_ptr<command_dto> config_parser::parse_action_set_temperature(action_type type, const std::string& value_path)
{
    return std::make_shared<parametrised_command_dto<double>>(type, get_value<double>(value_path));
}
