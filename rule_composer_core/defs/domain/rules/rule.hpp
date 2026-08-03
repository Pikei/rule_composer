/**
 * \file rule.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_RULE_HPP
#define RULE_COMPOSER_RULE_HPP

#include <id_types/id_types.hpp>
#include <memory>
#include <rules/commands/command_interface.hpp>
#include <rules/conditions/condition_node.hpp>
#include <vector>

using condition_t     = std::unique_ptr<condition_node>;
using action_t        = std::unique_ptr<command_interface>;
using action_iterator = std::vector<action_t>::const_iterator;

class rule
{
public:
    explicit rule(rule_id id, condition_t expression, std::vector<action_t> actions);

    [[nodiscard]]
    const condition_node& get_condition() const;

    [[nodiscard]]
    action_iterator begin() const;

    [[nodiscard]]
    action_iterator end() const;

private:
    rule_id               id;
    condition_t           expression;
    std::vector<action_t> actions;
};

#endif // RULE_COMPOSER_RULE_HPP
