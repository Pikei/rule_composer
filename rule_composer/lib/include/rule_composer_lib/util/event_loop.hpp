/**
 * \file event_loop.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_LIB_EVENT_LOOP_HPP
#define RULE_COMPOSER_LIB_EVENT_LOOP_HPP

#include <functional>

#include <event2/event.h>
#include <event2/thread.h>

namespace rule_composer::lib::util
{
    class event_loop
    {
    public:

        explicit event_loop( );
        ~event_loop( );

        event_loop( const event_loop& )            = delete;
        event_loop& operator=( const event_loop& ) = delete;

        void post( std::function< void( ) > task );

        [[nodiscard]]
        event_base* get_event_base( ) const;

        void run( );

        void stop( );

    private:

        static void on_once( evutil_socket_t fd, short events, void* arg );
        static void on_signal( evutil_socket_t signum, short events, void* arg );

        event_base* base { nullptr };

        event* sigint_event { nullptr };
        event* sigterm_event { nullptr };
    };
} // namespace rule_composer::lib::util
#endif // RULE_COMPOSER_LIB_EVENT_LOOP_HPP
