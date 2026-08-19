/**
 * \file main.cpp
 * Created by Piotr Karol 2026
 */

#include "../defs/sim_app.hpp"
#include "../defs/sim_options.hpp"

using namespace rule_composer::simulator;

int main( int argc, const char** argv )
{
    sim_options options;
    auto        args = options.parse( argc, argv );
    sim_app     app { args };
    app.run( );

    return 0;
}
