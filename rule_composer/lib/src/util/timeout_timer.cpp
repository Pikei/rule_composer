/**
 * \file timeout_timer.cpp
 * Created by Piotr Karol 2026
 */

#include <rule_composer_lib/util/timeout_timer.hpp>

namespace rule_composer::lib::util
{
    timeout_timer::timeout_timer( event_loop& loop_, std::chrono::milliseconds delay_, std::function< void( ) > callback_ ) :
        timer { event_new( loop_.get_event_base( ), -1, EV_TIMEOUT, &timeout_timer::on_timeout, this ), delay_, std::move( callback_ ) }
    {
    }

    void timeout_timer::on_timeout( evutil_socket_t, short, void* arg )
    {
        static_cast< timeout_timer* >( arg )->callback( );
    }
} // namespace rule_composer::lib::util
