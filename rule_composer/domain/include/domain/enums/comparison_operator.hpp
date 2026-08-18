/**
 * \file comparison_operator.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMPARISON_OPERATOR_HPP
#define RULE_COMPOSER_COMPARISON_OPERATOR_HPP

#include <cstdint>
#include <string>

namespace rule_composer::domain::enums
{
    enum class comparison_operator : std::uint8_t
    {
        unknown = 0,
        equal,
        not_equal,
        greater,
        greater_equal,
        less,
        less_equal,
    };
} // namespace rule_composer::domain::enums

inline const char* to_string( rule_composer::domain::enums::comparison_operator op )
{
    switch ( op )
    {
        case rule_composer::domain::enums::comparison_operator::equal:
            return "equal";
        case rule_composer::domain::enums::comparison_operator::not_equal:
            return "not_equal";
        case rule_composer::domain::enums::comparison_operator::greater:
            return "greater";
        case rule_composer::domain::enums::comparison_operator::greater_equal:
            return "greater_equal";
        case rule_composer::domain::enums::comparison_operator::less:
            return "less";
        case rule_composer::domain::enums::comparison_operator::less_equal:
            return "less_equal";
        default:
            return "unknown";
    }
}

inline rule_composer::domain::enums::comparison_operator str_to_comparison_operator( const std::string& str )
{
    if ( to_string( rule_composer::domain::enums::comparison_operator::equal ) == str )
    {
        return rule_composer::domain::enums::comparison_operator::equal;
    }
    if ( to_string( rule_composer::domain::enums::comparison_operator::not_equal ) == str )
    {
        return rule_composer::domain::enums::comparison_operator::not_equal;
    }
    if ( to_string( rule_composer::domain::enums::comparison_operator::greater ) == str )
    {
        return rule_composer::domain::enums::comparison_operator::greater;
    }
    if ( to_string( rule_composer::domain::enums::comparison_operator::greater_equal ) == str )
    {
        return rule_composer::domain::enums::comparison_operator::greater_equal;
    }
    if ( to_string( rule_composer::domain::enums::comparison_operator::less ) == str )
    {
        return rule_composer::domain::enums::comparison_operator::less;
    }
    if ( to_string( rule_composer::domain::enums::comparison_operator::less_equal ) == str )
    {
        return rule_composer::domain::enums::comparison_operator::less_equal;
    }
    return rule_composer::domain::enums::comparison_operator::unknown;
}

#endif // RULE_COMPOSER_COMPARISON_OPERATOR_HPP
