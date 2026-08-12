/**
 * \file condition_node.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_NODE_HPP
#define RULE_COMPOSER_CONDITION_NODE_HPP

#include <rules/context.hpp>

class condition_node
{
public:
    virtual ~condition_node() = default;
    [[nodiscard]]
    virtual bool evaluate(const context& ctx) const = 0;
};

#endif // RULE_COMPOSER_CONDITION_NODE_HPP
