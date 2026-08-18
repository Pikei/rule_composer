/**
 * \file logical_operator.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LOGICAL_OPERATOR_HPP
#define RULE_COMPOSER_LOGICAL_OPERATOR_HPP

#include <cstdint>
#include <string>

namespace rule_composer::domain::enums
{
    enum class logical_operator : std::uint8_t
    {
        unknown = 0,
        AND,
        OR,
    };
} // namespace rule_composer::domain::enums

inline const char* to_string( rule_composer::domain::enums::logical_operator e )
{
    switch ( e )
    {
        case rule_composer::domain::enums::logical_operator::AND:
            return "AND";
        case rule_composer::domain::enums::logical_operator::OR:
            return "OR";
        default:
            return "unknown";
    }
}

inline rule_composer::domain::enums::logical_operator str_to_logical_operator( const std::string& str )
{
    if ( to_string( rule_composer::domain::enums::logical_operator::AND ) == str )
    {
        return rule_composer::domain::enums::logical_operator::AND;
    }
    if ( to_string( rule_composer::domain::enums::logical_operator::OR ) == str )
    {
        return rule_composer::domain::enums::logical_operator::OR;
    }
    return rule_composer::domain::enums::logical_operator::unknown;
}

#endif // RULE_COMPOSER_LOGICAL_OPERATOR_HPP
