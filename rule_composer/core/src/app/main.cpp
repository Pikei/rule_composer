/**
 * \file main.cpp
 * Created by Piotr Karol 2026
 */

#include <app/app_options.hpp>
#include <app/core_app.hpp>

using namespace rule_composer::core::app;

int main( int argc, const char** argv )
{
    app_options options;
    auto        args = options.parse( argc, argv );
    core_app    app { args };
    app.run( );

    return 0;
}
