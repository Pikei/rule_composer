/**
 * \file logical_operator.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LOGICAL_OPERATOR_HPP
#define RULE_COMPOSER_LOGICAL_OPERATOR_HPP

#include <cstdint>
#include <string>

enum class logical_operator : std::uint8_t
{
    unknown = 0,
    AND,
    OR
};

inline const char* to_string(logical_operator e)
{
    switch (e)
    {
    case logical_operator::AND:
        return "AND";
    case logical_operator::OR:
        return "OR";
    default:
        return "unknown";
    }
}

inline logical_operator str_to_logical_operator(const std::string& str)
{
    if (to_string(logical_operator::AND) == str)
    {
        return logical_operator::AND;
    }
    if (to_string(logical_operator::OR) == str)
    {
        return logical_operator::OR;
    }
    return logical_operator::unknown;
}

#endif // RULE_COMPOSER_LOGICAL_OPERATOR_HPP
