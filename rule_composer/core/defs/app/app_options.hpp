/**
 * \file app_options.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_APP_OPTIONS_HPP
#define RULE_COMPOSER_APP_OPTIONS_HPP

#include <rule_composer_lib/app/app_options.hpp>

namespace rule_composer::core::app
{
    class app_options : public lib::app::app_options
    {
    public:

        explicit app_options( );

        static constexpr auto PROGRAM_NAME = "rule_composer_core";
        static constexpr auto PROGRAM_HELP = "help";

        static constexpr auto PARAM_CONFIG_PATH = "config-path";
        static constexpr auto DESC_CONFIG_PATH  = "Optional parameter used to specify path to configuration file.";

        static constexpr auto PARAM_EVAL_INTERVAL = "eval-interval";
        static constexpr auto DESC_EVAL_INTERVAL  = "Optional parameter used to specify interval of evaluation of rules conditions in milliseconds.";
    };
} // namespace rule_composer::core::app

#endif // RULE_COMPOSER_APP_OPTIONS_HPP
