/**
 * \file repeat_timer.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_LIB_REPEAT_TIMER_HPP
#define RULE_COMPOSER_LIB_REPEAT_TIMER_HPP

#include <chrono>
#include <functional>

#include <event2/event.h>
#include <rule_composer_lib/util/event_loop.hpp>
#include <rule_composer_lib/util/timer.hpp>

namespace rule_composer::lib::util
{
    class repeat_timer : public timer
    {
    public:

        explicit repeat_timer( event_loop& loop_, std::chrono::milliseconds interval_, std::function< void( ) > callback_ );

    private:

        static void on_repeat( evutil_socket_t fd, short events, void* arg );
    };
} // namespace rule_composer::lib::util

#endif // RULE_COMPOSER_LIB_REPEAT_TIMER_HPP
