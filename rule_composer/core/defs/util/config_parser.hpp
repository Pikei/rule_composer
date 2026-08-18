/**
 * \file config_parser.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONFIG_PARSER_HPP
#define RULE_COMPOSER_CONFIG_PARSER_HPP

#include <domain/enums/action_type.hpp>
#include <dto/configuration_dto.hpp>
#include <rule_composer_lib/util/json_utils.hpp>

namespace rule_composer::core::util
{
    class config_parser : public lib::util::json_utils
    {
    public:

        explicit config_parser( const std::shared_ptr< spdlog::logger >& logger_ );
        explicit config_parser( const std::string& file_path_, const std::shared_ptr< spdlog::logger >& logger_ );

        dto::configuration_dto parse_config( const std::string& file_path_ );
        dto::configuration_dto parse_config( );

    private:

        void parse_rooms( dto::configuration_dto& config );
        void parse_groups( dto::configuration_dto& config );
        void parse_devices( dto::configuration_dto& config );
        void parse_rules( dto::device_dto& device, std::size_t device_index );
        void parse_expression( dto::condition_dto& condition, const std::string& exp_path );
        void parse_simple_expression( dto::condition_dto& condition, const std::string& exp_path );
        void parse_compound_expression( dto::condition_dto& condition, const std::string& exp_path );
        void parse_actions( dto::rule_dto& rule, const std::string& rule_path );

        std::shared_ptr< dto::command_dto > parse_action( domain::enums::action_type type, const std::string& action_path );
        std::shared_ptr< dto::command_dto > parse_action_set_light_color( domain::enums::action_type type, const std::string& value_path );
    };
} // namespace rule_composer::core::util
#endif // RULE_COMPOSER_CONFIG_PARSER_HPP
