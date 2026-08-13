/**
 * \file comparison_operator.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMPARISON_OPERATOR_HPP
#define RULE_COMPOSER_COMPARISON_OPERATOR_HPP

#include <cstdint>
#include <string>

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

inline const char* to_string( comparison_operator op )
{
    switch ( op )
    {
        case comparison_operator::equal:
            return "equal";
        case comparison_operator::not_equal:
            return "not_equal";
        case comparison_operator::greater:
            return "greater";
        case comparison_operator::greater_equal:
            return "greater_equal";
        case comparison_operator::less:
            return "less";
        case comparison_operator::less_equal:
            return "less_equal";
        default:
            return "unknown";
    }
}

inline comparison_operator str_to_comparison_operator( const std::string& str )
{
    if ( to_string( comparison_operator::equal ) == str )
    {
        return comparison_operator::equal;
    }
    if ( to_string( comparison_operator::not_equal ) == str )
    {
        return comparison_operator::not_equal;
    }
    if ( to_string( comparison_operator::greater ) == str )
    {
        return comparison_operator::greater;
    }
    if ( to_string( comparison_operator::greater_equal ) == str )
    {
        return comparison_operator::greater_equal;
    }
    if ( to_string( comparison_operator::less ) == str )
    {
        return comparison_operator::less;
    }
    if ( to_string( comparison_operator::less_equal ) == str )
    {
        return comparison_operator::less_equal;
    }
    return comparison_operator::unknown;
}

#endif // RULE_COMPOSER_COMPARISON_OPERATOR_HPP
