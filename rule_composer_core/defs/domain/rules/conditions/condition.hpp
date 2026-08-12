/**
 * \file condition.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_HPP
#define RULE_COMPOSER_CONDITION_HPP

#include <enums/comparison_operator.hpp>
#include <enums/condition_type.hpp>
#include <enums/weekday.hpp>

#include <chrono>
#include <cstdint>
#include <rules/conditions/condition_node.hpp>
#include <variant>

using condition_value = std::variant<std::chrono::minutes, weekday, double>;

class condition : public condition_node
{
public:
    explicit condition(condition_type type, comparison_operator comparison, condition_value value);
    [[nodiscard]]
    bool evaluate(const context& ctx) const override;

    [[nodiscard]]
    condition_type get_type() const;

    [[nodiscard]]
    comparison_operator get_comparison() const;

    [[nodiscard]]
    condition_value get_value() const;

private:
    const condition_type      type;
    const comparison_operator comparison;
    const condition_value     value;

    bool evaluate_time(const context& ctx) const;
    bool evaluate_weekday(const context& ctx) const;
    bool evaluate_temperature(const context& ctx) const;
};

#endif // RULE_COMPOSER_CONDITION_HPP
