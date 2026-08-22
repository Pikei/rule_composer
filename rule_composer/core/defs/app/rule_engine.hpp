/**
 * \file rule_engine.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_RULE_ENGINE_HPP
#define RULE_COMPOSER_RULE_ENGINE_HPP

#include <map>

#include <domain/rules/rule.hpp>
#include <dto/configuration_dto.hpp>
#include <rule_composer_lib/util/event_loop.hpp>
#include <rule_composer_lib/util/repeat_timer.hpp>
#include <spdlog/spdlog.h>

namespace rule_composer::core::app
{
    class rule_engine
    {
    public:

        explicit rule_engine( lib::util::event_loop&             loop,
                              std::shared_ptr< spdlog::logger >& logger_,
                              std::uint32_t                      eval_interval_,
                              domain::rules::context&            ctx_ );
        void parse_config_dto( const dto::configuration_dto& config );
        void start( );
        void stop( );

    private:

        lib::util::repeat_timer                                      timer;
        domain::rules::context&                                      ctx;
        std::map< domain::id_types::device_id, domain::rules::rule > rules;
        std::map< domain::id_types::rule_id, bool >                  triggered;
        std::shared_ptr< spdlog::logger >&                           logger;

        void evaluate_rules( );
    };
} // namespace rule_composer::core::app

#endif // RULE_COMPOSER_RULE_ENGINE_HPP
