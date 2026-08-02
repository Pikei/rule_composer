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
    condition(const condition_type type, const comparison_operator comparison, const condition_value value) : type(type),
                                                                                                              comparison(comparison),
                                                                                                              value(value) { }
    [[nodiscard]]
    bool evaluate(const context& ctx) const override;

    void accept(const condition_visitor& visitor) const override;

    [[nodiscard]]
    condition_type get_type() const
    {
        return type;
    }

    comparison_operator get_comparison() const
    {
        return comparison;
    }
    condition_value get_value() const
    {
        return value;
    }

private:
    const condition_type      type;
    const comparison_operator comparison;
    const condition_value     value;
};

#endif // RULE_COMPOSER_CONDITION_HPP
