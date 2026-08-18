/**
 * \file rule.cpp
 * Created by Piotr Karol 2026
 */
#include <domain/rules/rule.hpp>

namespace rule_composer::domain::rules
{
    rule::rule( id_types::rule_id id, condition_t expression, std::vector< action_t > actions ) :
        id( id ),
        expression( std::move( expression ) ),
        actions( std::move( actions ) )
    {
    }

    const conditions::condition_node& rule::get_condition( ) const
    {
        return *expression;
    }

    id_types::rule_id rule::get_id( ) const
    {
        return id;
    }

    action_iterator rule::begin( ) const
    {
        return actions.begin( );
    }

    action_iterator rule::end( ) const
    {
        return actions.end( );
    }
} // namespace rule_composer::domain::rules
