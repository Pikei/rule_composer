/**
 * \file timer.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LIB_TIMER_HPP
#define RULE_COMPOSER_LIB_TIMER_HPP

#include <chrono>
#include <functional>

#include <event2/event.h>
#include <rule_composer_lib/util/event_loop.hpp>

namespace rule_composer::lib::util
{
    class timer
    {
    public:

        virtual ~timer( );
        void start( );
        void stop( );

        [[nodiscard]]
        bool is_running( ) const;

        void set_chrono( std::chrono::milliseconds chrono_ );

    protected:

        explicit timer( event* time_event_, std::chrono::milliseconds time_, std::function< void( ) > callback_ );

        event*                    time_event { nullptr };
        std::chrono::milliseconds chrono { 0 };
        std::function< void( ) >  callback;

    private:

        bool        running = false;
        static void on_trigger( evutil_socket_t fd, short events, void* arg );
    };
} // namespace rule_composer::lib::util

#endif // RULE_COMPOSER_LIB_TIMER_HPP
