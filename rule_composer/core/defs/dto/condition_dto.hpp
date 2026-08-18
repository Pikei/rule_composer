/**
 * \file condition_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_DTO_HPP
#define RULE_COMPOSER_CONDITION_DTO_HPP

#include <optional>
#include <vector>

#include <domain/enums/comparison_operator.hpp>
#include <domain/enums/condition_type.hpp>
#include <domain/enums/logical_operator.hpp>
#include <domain/rules/conditions/condition.hpp>

namespace rule_composer::core::dto
{
    struct condition_dto
    {
        std::optional< domain::enums::condition_type >              type;
        std::optional< domain::enums::comparison_operator >         comp_op;
        std::optional< domain::rules::conditions::condition_value > value;

        std::optional< domain::enums::logical_operator > log_op;
        std::vector< condition_dto >                     children;
    };
} // namespace rule_composer::core::dto

#endif // RULE_COMPOSER_CONDITION_DTO_HPP
