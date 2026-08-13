/**
 * \file repeat_timer.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_REPEAT_TIMER_HPP
#define RULE_COMPOSER_REPEAT_TIMER_HPP

#include <chrono>
#include <functional>

#include <event2/event.h>

class repeat_timer
{
public:

    explicit repeat_timer( event_base* base_, std::chrono::milliseconds interval_, std::function< void( ) > callback_ );
    ~repeat_timer( );

    void start( );
    void stop( );

    [[nodiscard]]
    bool is_running( ) const;

private:

    static void on_repeat( evutil_socket_t fd, short events, void* arg );

    event_base*               base;
    std::chrono::milliseconds interval;
    std::function< void( ) >  callback;
    event*                    time_event { nullptr };
    bool                      running { false };
};

#endif // RULE_COMPOSER_REPEAT_TIMER_HPP
