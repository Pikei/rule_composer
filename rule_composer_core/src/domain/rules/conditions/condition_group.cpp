/**
 * \file condition_group.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/conditions/condition_group.hpp>

bool condition_group::evaluate(const context& ctx) const
{
    return false;
}

void condition_group::add_child(node_ptr child)
{
}

iterator condition_group::begin() const
{
    return children.begin();
}

iterator condition_group::end() const
{
    return children.end();
}

logical_operator condition_group::get_logical_operator() const
{
    return op;
}