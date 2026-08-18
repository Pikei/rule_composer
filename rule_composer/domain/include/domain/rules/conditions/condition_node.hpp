/**
 * \file condition_node.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_NODE_HPP
#define RULE_COMPOSER_CONDITION_NODE_HPP

#include <domain/rules/context.hpp>

namespace rule_composer::domain::rules::conditions
{
    class condition_node
    {
    public:

        virtual ~condition_node( ) = default;
        [[nodiscard]]
        virtual bool evaluate( const context& ctx ) const = 0;
    };
} // namespace rule_composer::domain::rules::conditions

#endif // RULE_COMPOSER_CONDITION_NODE_HPP
