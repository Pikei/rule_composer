/**
 * \file event_loop.hpp
 * Created by Piotr Karol 2026
 */

#ifndef RULE_COMPOSER_EVENT_LOOP_HPP
#define RULE_COMPOSER_EVENT_LOOP_HPP

#include <app/repeat_timer.hpp>
#include <app/timeout_timer.hpp>
#include <event2/event.h>
#include <event2/thread.h>
#include <functional>
#include <memory>

class event_loop
{
public:
    explicit event_loop();
    ~event_loop();

    event_loop(const event_loop&)            = delete;
    event_loop& operator=(const event_loop&) = delete;

    void post(std::function<void()> task);

    repeat_timer  create_repeat_timer(std::chrono::milliseconds interval, std::function<void()> callback);
    timeout_timer create_timeout_timer(std::function<void()> callback);

    void run();

    void stop();

private:
    static void on_once(evutil_socket_t fd, short events, void* arg);
    static void on_signal(evutil_socket_t signum, short events, void* arg);

    event_base* base { nullptr };

    event* sigint_event { nullptr };
    event* sigterm_event { nullptr };
};

#endif // RULE_COMPOSER_EVENT_LOOP_HPP
