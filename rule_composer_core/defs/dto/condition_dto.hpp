/**
 * \file condition_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_DTO_HPP
#define RULE_COMPOSER_CONDITION_DTO_HPP

#include <enums/comparison_operator.hpp>
#include <enums/condition_type.hpp>
#include <enums/logical_operator.hpp>
#include <optional>
#include <rules/conditions/condition.hpp>
#include <vector>

struct condition_dto
{
    std::optional<condition_type>      type;
    std::optional<comparison_operator> comp_op;
    std::optional<condition_value>     value;

    std::optional<logical_operator> log_op;
    std::vector<condition_dto>      children;
};

#endif // RULE_COMPOSER_CONDITION_DTO_HPP
