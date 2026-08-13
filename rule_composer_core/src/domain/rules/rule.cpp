/**
 * \file rule.cpp
 * Created by Piotr Karol 2026
 */
#include <rules/conditions/condition.hpp>
#include <rules/rule.hpp>

rule::rule( rule_id id, condition_t expression, std::vector< action_t > actions ) :
    id( id ),
    expression( std::move( expression ) ),
    actions( std::move( actions ) )
{
}

const condition_node& rule::get_condition( ) const
{
    return *expression;
}

rule_id rule::get_id( ) const
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
