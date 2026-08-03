/**
 * \file context.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONTEXT_HPP
#define RULE_COMPOSER_CONTEXT_HPP

#include <chrono>
#include <enums/weekday.hpp>

struct current_time
{
    std::chrono::hours   hour;
    std::chrono::minutes minutes;
};

class context_if
{
public:
    virtual ~context_if() = default;

    [[nodiscard]]
    virtual current_time get_current_time() const = 0;

    [[nodiscard]]
    virtual weekday get_weekday() const = 0;

    [[nodiscard]]
    virtual std::uint8_t get_temperature() const = 0;
};

class context : public context_if
{
public:
    [[nodiscard]]
    current_time get_current_time() const override;

    [[nodiscard]]
    weekday get_weekday() const override;

    [[nodiscard]]
    std::uint8_t get_temperature() const override;
};

#endif // RULE_COMPOSER_CONTEXT_HPP
