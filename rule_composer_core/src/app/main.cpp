/**
 * \file main.cpp
 * Created by Piotr Karol 2026
 */

#include <app/app_options.hpp>
#include <app/application.hpp>

int main(int argc, const char** argv)
{
    app_options options;
    auto        args = options.parse(argc, argv);
    application app { args };

    return 0;
}
