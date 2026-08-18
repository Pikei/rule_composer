/**
 * \file rule.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_RULE_HPP
#define RULE_COMPOSER_RULE_HPP

#include <memory>
#include <vector>

#include <domain/id_types/id_types.hpp>
#include <domain/rules/commands/command_interface.hpp>
#include <domain/rules/conditions/condition_node.hpp>

namespace rule_composer::domain::rules
{
    using condition_t     = std::unique_ptr< conditions::condition_node >;
    using action_t        = std::unique_ptr< command_interface >;
    using action_iterator = std::vector< action_t >::const_iterator;

    class rule
    {
    public:

        explicit rule( id_types::rule_id id, condition_t expression, std::vector< action_t > actions );

        [[nodiscard]]
        const conditions::condition_node& get_condition( ) const;

        [[nodiscard]]
        id_types::rule_id get_id( ) const;

        [[nodiscard]]
        action_iterator begin( ) const;

        [[nodiscard]]
        action_iterator end( ) const;

    private:

        id_types::rule_id       id;
        condition_t             expression;
        std::vector< action_t > actions;
    };
} // namespace rule_composer::domain::rules

#endif // RULE_COMPOSER_RULE_HPP
