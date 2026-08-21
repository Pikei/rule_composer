/**
 * \file command_visitor.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMMAND_VISITOR_HPP
#define RULE_COMPOSER_COMMAND_VISITOR_HPP

namespace rule_composer::domain::rules::commands::thermostat
{
    class set_temperature;
}

namespace rule_composer::domain::rules::commands::socket
{
    class turn_off;
    class turn_on;
} // namespace rule_composer::domain::rules::commands::socket

namespace rule_composer::domain::rules::commands::curtains
{
    class open;
    class close;
    class set_position;
} // namespace rule_composer::domain::rules::commands::curtains

namespace rule_composer::domain::rules::commands::light
{
    class turn_on;
    class turn_off;
    class set_brightness;
    class set_color;
} // namespace rule_composer::domain::rules::commands::light

namespace rule_composer::core::util
{
    class command_visitor
    {
    public:

        virtual ~command_visitor( ) = default;

        virtual void visit( const domain::rules::commands::light::turn_on& cmd )        = 0;
        virtual void visit( const domain::rules::commands::light::turn_off& cmd )       = 0;
        virtual void visit( const domain::rules::commands::light::set_brightness& cmd ) = 0;
        virtual void visit( const domain::rules::commands::light::set_color& cmd )      = 0;

        virtual void visit( const domain::rules::commands::curtains::open& cmd )         = 0;
        virtual void visit( const domain::rules::commands::curtains::close& cmd )        = 0;
        virtual void visit( const domain::rules::commands::curtains::set_position& cmd ) = 0;

        virtual void visit( const domain::rules::commands::socket::turn_on& cmd )  = 0;
        virtual void visit( const domain::rules::commands::socket::turn_off& cmd ) = 0;

        virtual void visit( const domain::rules::commands::thermostat::set_temperature& cmd ) = 0;
    };

} // namespace rule_composer::core::util

#endif // RULE_COMPOSER_COMMAND_VISITOR_HPP
