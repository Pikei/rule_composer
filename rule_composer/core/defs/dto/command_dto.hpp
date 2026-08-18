/**
 * \file command_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMMAND_DTO_HPP
#define RULE_COMPOSER_COMMAND_DTO_HPP

#include <domain/enums/action_type.hpp>

namespace rule_composer::core::dto
{
    class command_dto
    {
    public:

        explicit command_dto( domain::enums::action_type type ) : type( type )
        {
        }
        virtual ~command_dto( ) = default;

        [[nodiscard]]
        domain::enums::action_type get_type( ) const
        {
            return type;
        }

    private:

        domain::enums::action_type type;
    };

    template < typename T >
    class parametrised_command_dto : public command_dto
    {
    public:

        explicit parametrised_command_dto( domain::enums::action_type type, const T& value ) : command_dto( type ), value( value )
        {
        }
        const T& get_value( ) const
        {
            return value;
        }

    private:

        T value;
    };
} // namespace rule_composer::core::dto

#endif // RULE_COMPOSER_COMMAND_DTO_HPP
