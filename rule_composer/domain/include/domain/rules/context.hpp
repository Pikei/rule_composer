/**
 * \file context.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONTEXT_HPP
#define RULE_COMPOSER_CONTEXT_HPP

#include <chrono>

#include <domain/enums/weekday.hpp>

namespace rule_composer::domain::rules
{
    class context_interface
    {
    public:

        virtual ~context_interface( ) = default;

        [[nodiscard]]
        virtual std::chrono::minutes get_current_time( ) const = 0;

        [[nodiscard]]
        virtual enums::weekday get_weekday( ) const = 0;

        [[nodiscard]]
        virtual double get_temperature( ) const = 0;
    };

    class context : public context_interface
    {
    public:

        [[nodiscard]]
        std::chrono::minutes get_current_time( ) const override;

        [[nodiscard]]
        enums::weekday get_weekday( ) const override;

        [[nodiscard]]
        double get_temperature( ) const override;
    };

    class test_context : public context_interface
    {
    public:

        [[nodiscard]]
        std::chrono::minutes get_current_time( ) const override
        {
            return std::chrono::minutes { 1200 };
        }
        [[nodiscard]]
        enums::weekday get_weekday( ) const override
        {
            return enums::weekday::saturday;
        }
        [[nodiscard]]
        double get_temperature( ) const override
        {
            return 22;
        }
    };
} // namespace rule_composer::domain::rules

#endif // RULE_COMPOSER_CONTEXT_HPP
