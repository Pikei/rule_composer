/**
 * \file context.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONTEXT_HPP
#define RULE_COMPOSER_CONTEXT_HPP

#include <chrono>

#include <enums/weekday.hpp>

class context_interface
{
public:

    virtual ~context_interface( ) = default;

    [[nodiscard]]
    virtual std::chrono::minutes get_current_time( ) const = 0;

    [[nodiscard]]
    virtual weekday get_weekday( ) const = 0;

    [[nodiscard]]
    virtual double get_temperature( ) const = 0;
};

class context : public context_interface
{
public:

    [[nodiscard]]
    std::chrono::minutes get_current_time( ) const override;

    [[nodiscard]]
    weekday get_weekday( ) const override;

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
    weekday get_weekday( ) const override
    {
        return weekday::saturday;
    }
    [[nodiscard]]
    double get_temperature( ) const override
    {
        return 22;
    }
};

#endif // RULE_COMPOSER_CONTEXT_HPP
