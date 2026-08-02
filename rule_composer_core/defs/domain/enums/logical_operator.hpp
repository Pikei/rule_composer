/**
 * \file logical_operator.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LOGICAL_OPERATOR_HPP
#define RULE_COMPOSER_LOGICAL_OPERATOR_HPP

#include <cstdint>

enum class logical_operator : std::uint8_t
{
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

#endif // RULE_COMPOSER_LOGICAL_OPERATOR_HPP
