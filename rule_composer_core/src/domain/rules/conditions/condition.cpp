/**
 * \file condition.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/conditions/condition.hpp>

condition::condition(const condition_type type, const comparison_operator comparison, const condition_value value) :
    type { type },
    comparison { comparison },
    value { value }
{
}

bool condition::evaluate(const context& ctx) const
{
    return false;
}
