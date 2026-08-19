/**
 * \file sim_options.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_SIM_OPTIONS_HPP
#define RULE_COMPOSER_SIM_OPTIONS_HPP

#include <rule_composer_lib/app/app_options.hpp>

namespace rule_composer::simulator
{

    class sim_options : public lib::app::app_options
    {
    public:

        explicit sim_options( );

        static constexpr auto PROGRAM_NAME = "light_simulator";
        static constexpr auto PROGRAM_HELP = "";

        static constexpr auto PARAM_NAME = "name";
        static constexpr auto DESC_NAME  = "Light device name";

        static constexpr auto PARAM_ID = "id";
        static constexpr auto DESC_ID  = "Light device ID";

        static constexpr auto PARAM_BRIGHTNESS = "brightness";
        static constexpr auto DESC_BRIGHTNESS  = "Optional flag describing ability to set brightness";

        static constexpr auto PARAM_COLOR = "color";
        static constexpr auto DESC_COLOR  = "Optional flag describing ability to set color";
    };

} // namespace rule_composer::simulator

#endif // RULE_COMPOSER_SIM_OPTIONS_HPP
