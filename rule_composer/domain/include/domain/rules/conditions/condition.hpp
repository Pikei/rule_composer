/**
 * \file condition.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONDITION_HPP
#define RULE_COMPOSER_CONDITION_HPP

#include <chrono>
#include <variant>

#include <domain/enums/comparison_operator.hpp>
#include <domain/enums/condition_type.hpp>
#include <domain/enums/weekday.hpp>
#include <domain/rules/conditions/condition_node.hpp>

namespace rule_composer::domain::rules::conditions
{
    using condition_value = std::variant< std::chrono::minutes, enums::weekday, double >;

    class condition : public condition_node
    {
    public:

        explicit condition( enums::condition_type type, enums::comparison_operator comparison, condition_value value );
        [[nodiscard]]
        bool evaluate( const context_interface& ctx ) const override;

        [[nodiscard]]
        enums::condition_type get_type( ) const;

        [[nodiscard]]
        enums::comparison_operator get_comparison( ) const;

        [[nodiscard]]
        condition_value get_value( ) const;

    private:

        const enums::condition_type      type;
        const enums::comparison_operator comparison;
        const condition_value            value;

        [[nodiscard]]
        bool evaluate_time( const context_interface& ctx ) const;
        [[nodiscard]]
        bool evaluate_weekday( const context_interface& ctx ) const;
        [[nodiscard]]
        bool evaluate_temperature( const context_interface& ctx ) const;
        [[nodiscard]]
        bool evaluate_humidity( const context_interface& ctx ) const;
    };
} // namespace rule_composer::domain::rules::conditions

#endif // RULE_COMPOSER_CONDITION_HPP
