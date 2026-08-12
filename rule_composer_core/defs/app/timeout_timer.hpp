/**
 * \file timeout_timer.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_TIMEOUT_TIMER_HPP
#define RULE_COMPOSER_TIMEOUT_TIMER_HPP

#include <chrono>
#include <event2/event.h>
#include <functional>

class timeout_timer
{
public:
    explicit timeout_timer(event_base* base_, std::function<void()> callback_);
    ~timeout_timer();

    timeout_timer(const timeout_timer&)            = delete;
    timeout_timer& operator=(const timeout_timer&) = delete;

    void start(std::chrono::milliseconds delay);

    void stop();

private:
    static void on_timeout(evutil_socket_t fd, short events, void* arg);

    std::function<void()> callback;
    event*                time_event = { nullptr };
};

#endif // RULE_COMPOSER_TIMEOUT_TIMER_HPP
