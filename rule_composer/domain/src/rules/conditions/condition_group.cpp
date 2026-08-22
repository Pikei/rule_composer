/**
 * \file condition_group.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/conditions/condition_group.hpp>

namespace rule_composer::domain::rules::conditions
{
    bool condition_group::evaluate( const context_interface& ctx ) const
    {
        if ( op == enums::logical_operator::AND )
        {
            for ( const auto& child : children )
            {
                if ( !child->evaluate( ctx ) )
                {
                    return false;
                }
            }
            return true;
        }
        if ( op == enums::logical_operator::OR )
        {
            for ( const auto& child : children )
            {
                if ( child->evaluate( ctx ) )
                {
                    return true;
                }
            }
            return false;
        }
        return false;
    }

    enums::logical_operator condition_group::get_logical_operator( ) const
    {
        return op;
    }

    void condition_group::add( node_ptr child )
    {
        children.push_back( std::move( child ) );
    }
} // namespace rule_composer::domain::rules::conditions
