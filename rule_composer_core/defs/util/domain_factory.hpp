/**
 * \file domain_factory.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DOMAIN_FACTORY_HPP
#define RULE_COMPOSER_DOMAIN_FACTORY_HPP

#include <vector>

#include <dto/configuration_dto.hpp>
#include <entities/group.hpp>
#include <entities/room.hpp>
#include <rules/rule.hpp>

class domain_factory
{
public:

    static std::vector< room >                                 create_rooms( const configuration_dto& dto );
    static std::vector< group >                                create_groups( const configuration_dto& dto );
    static std::vector< device >                               create_devices( const configuration_dto& dto );
    static rule                                                create_rule( const rule_dto& dto );
    static std::unique_ptr< condition_node >                   create_condition( const condition_dto& dto );
    static std::vector< std::unique_ptr< command_interface > > create_commands( const rule_dto& dto );
    static std::unique_ptr< command_interface >                create_command( const command_dto& dto );

    template < typename cmd_type, typename param_type >
    static std::unique_ptr< cmd_type > create_parametrised_command( const command_dto& dto )
    {
        const auto* param_value = dynamic_cast< const parametrised_command_dto< param_type >* >( &dto );
        if ( nullptr == param_value )
        {
            return nullptr;
        }
        return std::make_unique< cmd_type >( static_cast< param_type >( param_value->get_value( ) ) );
    }
};

#endif // RULE_COMPOSER_DOMAIN_FACTORY_HPP
