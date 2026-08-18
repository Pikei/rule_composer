/**
 * \file domain_factory.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DOMAIN_FACTORY_HPP
#define RULE_COMPOSER_DOMAIN_FACTORY_HPP

#include <vector>

#include <domain/entities/group.hpp>
#include <domain/entities/room.hpp>
#include <domain/rules/rule.hpp>
#include <dto/configuration_dto.hpp>

namespace rule_composer::core::util
{
    class domain_factory
    {
    public:

        static std::vector< domain::entities::room >                              create_rooms( const dto::configuration_dto& dto );
        static std::vector< domain::entities::group >                             create_groups( const dto::configuration_dto& dto );
        static std::vector< domain::entities::device >                            create_devices( const dto::configuration_dto& dto );
        static domain::rules::rule                                                create_rule( const dto::rule_dto& dto );
        static std::unique_ptr< domain::rules::conditions::condition_node >       create_condition( const dto::condition_dto& dto );
        static std::vector< std::unique_ptr< domain::rules::command_interface > > create_commands( const dto::rule_dto& dto );
        static std::unique_ptr< domain::rules::command_interface >                create_command( const dto::command_dto& dto );

        template < typename cmd_type, typename param_type >
        static std::unique_ptr< cmd_type > create_parametrised_command( const dto::command_dto& dto )
        {
            const auto* param_value = dynamic_cast< const dto::parametrised_command_dto< param_type >* >( &dto );
            if ( nullptr == param_value )
            {
                return nullptr;
            }
            return std::make_unique< cmd_type >( static_cast< param_type >( param_value->get_value( ) ) );
        }
    };
} // namespace rule_composer::core::util
#endif // RULE_COMPOSER_DOMAIN_FACTORY_HPP
