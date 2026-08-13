/**
 * \file rule_engine.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_RULE_ENGINE_HPP
#define RULE_COMPOSER_RULE_ENGINE_HPP

#include <map>

#include <app/event_loop.hpp>
#include <app/repeat_timer.hpp>
#include <dto/configuration_dto.hpp>
#include <id_types/id_types.hpp>
#include <rules/rule.hpp>
#include <spdlog/spdlog.h>

class rule_engine
{
public:

    explicit rule_engine( event_loop& loop, std::shared_ptr< spdlog::logger >& logger_, configuration_dto& config );
    void start( );

private:

    repeat_timer                       timer;
    std::map< device_id, rule >        rules;
    std::shared_ptr< spdlog::logger >& logger;

    void evaluate_rules( );
};

#endif // RULE_COMPOSER_RULE_ENGINE_HPP
