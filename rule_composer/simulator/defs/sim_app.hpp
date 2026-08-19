/**
 * \file sim_app.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_SIM_APP_HPP
#define RULE_COMPOSER_SIM_APP_HPP

#include <rule_composer_lib/app/application.hpp>
#include <sim_options.hpp>

namespace rule_composer::simulator
{

    class sim_app : public lib::app::application
    {
    public:

        explicit sim_app( const cxxopts::ParseResult& args );

    protected:

        void before_run( ) override;
    };

} // namespace rule_composer::simulator

#endif // RULE_COMPOSER_SIM_APP_HPP
