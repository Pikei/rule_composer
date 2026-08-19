/**
 * \file sim_app.cpp
 * Created by Piotr Karol 2026
 */
#include <sim_app.hpp>

namespace rule_composer::simulator
{
    sim_app::sim_app( const cxxopts::ParseResult& args ) : application { args, sim_options::PROGRAM_NAME }
    {
    }

    void sim_app::before_run( )
    {
        auto id                     = args[sim_options::PARAM_ID].as< std::uint16_t >( );
        auto name                   = args[sim_options::PARAM_NAME].as< std::string >( );
        bool able_to_set_brightness = args[sim_options::PARAM_BRIGHTNESS].count( ) > 0;
        bool able_to_set_color      = args[sim_options::PARAM_COLOR].count( ) > 0;
    }
} // namespace rule_composer::simulator
