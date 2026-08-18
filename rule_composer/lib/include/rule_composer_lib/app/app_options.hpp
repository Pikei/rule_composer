/**
 * \file app_options.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LIB_APP_OPTIONS_HPP
#define RULE_COMPOSER_LIB_APP_OPTIONS_HPP

#include <cxxopts.hpp>

namespace rule_composer::lib::app
{
    class app_options
    {
    public:

        virtual ~app_options( ) = default;

        static constexpr auto PARAM_LOG_LEVEL = "log-level";
        static constexpr auto DESC_LOG_LEVEL  = "Optional parameter used to specify the application logger level (trace|debug|info|warn|error|critical|off).";

        explicit app_options( const std::string& program_name, const std::string& program_help );
        cxxopts::ParseResult parse( int& argc, const char**& argv );

    protected:

        cxxopts::Options options;
    };

} // namespace rule_composer::lib::app

#endif // RULE_COMPOSER_LIB_APP_OPTIONS_HPP
