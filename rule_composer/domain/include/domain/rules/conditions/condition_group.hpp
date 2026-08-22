/**
 * \file condition_group.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_GROUP_HPP
#define RULE_COMPOSER_CONDITION_GROUP_HPP

#include <memory>
#include <vector>

#include <domain/enums/logical_operator.hpp>
#include <domain/rules/conditions/condition_node.hpp>

namespace rule_composer::domain::rules::conditions
{
    using node_ptr = std::unique_ptr< condition_node >;

    class condition_group : public condition_node
    {
    public:

        explicit condition_group( enums::logical_operator op ) : op( op )
        {
        }

        [[nodiscard]]
        bool evaluate( const context_interface& ctx ) const override;

        [[nodiscard]]
        enums::logical_operator get_logical_operator( ) const;

        void add( node_ptr child );

    private:

        const enums::logical_operator op;
        std::vector< node_ptr >       children;
    };
} // namespace rule_composer::domain::rules::conditions

#endif // RULE_COMPOSER_CONDITION_GROUP_HPP
