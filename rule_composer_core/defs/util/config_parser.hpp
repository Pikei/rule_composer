/**
 * \file config_parser.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONFIG_PARSER_HPP
#define RULE_COMPOSER_CONFIG_PARSER_HPP

#include <dto/configuration_dto.hpp>
#include <util/json_utils.hpp>

class config_parser : public json_utils
{
public:
    explicit config_parser(const logger_t& logger_);
    explicit config_parser(const std::string& file_path_, const logger_t& logger_);

    configuration_dto parse_config(const std::string& file_path_);
    configuration_dto parse_config();

    void                         parse_rooms(configuration_dto& config);
    void                         parse_groups(configuration_dto& config);
    void                         parse_devices(configuration_dto& config);
    void                         parse_rules(device_dto& device, std::size_t device_index);
    void                         parse_expression(condition_dto& condition, const std::string& exp_path);
    void                         parse_simple_expression(condition_dto& condition, const std::string& exp_path);
    void                         parse_compound_expression(condition_dto& condition, const std::string& exp_path);
    void                         parse_actions(rule_dto& rule, const std::string& rule_path);
    std::shared_ptr<command_dto> parse_action(action_type type, const std::string& action_path);
    std::shared_ptr<command_dto> parse_action_turn_on_light(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_turn_off_light(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_set_brightness(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_set_light_color(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_turn_on_socket(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_turn_off_socket(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_open_curtain(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_close_curtain(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_set_curtain_position(action_type type, const std::string& value_path);
    std::shared_ptr<command_dto> parse_action_set_temperature(action_type type, const std::string& value_path);
};

#endif // RULE_COMPOSER_CONFIG_PARSER_HPP
