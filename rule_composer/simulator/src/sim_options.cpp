/**
 * \file sim_options.cpp
 * Created by Piotr Karol 2026
 */
#include <sim_options.hpp>

namespace rule_composer::simulator
{
    sim_options::sim_options( ) : app_options { PROGRAM_NAME, PROGRAM_HELP }
    {
        auto general = options.add_options( );
        general( PARAM_ID, DESC_ID, cxxopts::value< std::uint16_t >( )->default_value( "0" ) );
        general( PARAM_NAME, DESC_NAME, cxxopts::value< std::string >( )->default_value( "Test Light device" ) );
        general( PARAM_BRIGHTNESS, DESC_BRIGHTNESS );
        general( PARAM_COLOR, DESC_COLOR );
    }

} // namespace rule_composer::simulator
