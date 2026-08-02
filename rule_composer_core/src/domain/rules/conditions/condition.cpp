/**
 * \file condition.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/conditions/condition.hpp>

bool condition::evaluate(const context& ctx) const
{
    return false;
}

void condition::accept(const condition_visitor& visitor) const
{
}
