/**
 * \file condition_group.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_GROUP_HPP
#define RULE_COMPOSER_CONDITION_GROUP_HPP

#include <enums/logical_operator.hpp>
#include <memory>
#include <rules/conditions/condition_node.hpp>
#include <vector>

using node_ptr      = std::unique_ptr<condition_node>;

class condition_group : public condition_node
{
public:
    explicit condition_group(logical_operator op) : op(op) { }

    [[nodiscard]]
    bool evaluate(const context& ctx) const override;

    [[nodiscard]]
    logical_operator get_logical_operator() const;

private:
    const logical_operator op;
    std::vector<node_ptr>  children;
};

#endif // RULE_COMPOSER_CONDITION_GROUP_HPP
