/**
 * \file condition_group.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/conditions/condition_group.hpp>

bool condition_group::evaluate(const context& ctx) const
{
    if (op == logical_operator::AND)
    {
        for (const auto& child : children)
        {
            if (!child->evaluate(ctx))
            {
                return false;
            }
        }
        return true;
    }
    if (op == logical_operator::OR)
    {
        for (const auto& child : children)
        {
            if (child->evaluate(ctx))
            {
                return true;
            }
        }
        return false;
    }
    return false;
}

logical_operator condition_group::get_logical_operator() const
{
    return op;
}