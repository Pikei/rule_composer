/**
 * \file repeat_timer.cpp
 * Created by Piotr Karol 2026
 */

#include <rule_composer_lib/util/repeat_timer.hpp>

namespace rule_composer::lib::util
{
    repeat_timer::repeat_timer( event_loop& loop_, std::chrono::milliseconds interval_, std::function< void( ) > callback_ ) :
        timer { event_new( loop_.get_event_base( ), -1, EV_PERSIST, &repeat_timer::on_repeat, this ), interval_, std::move( callback_ ) }
    {
    }

    void repeat_timer::on_repeat( evutil_socket_t, short, void* arg )
    {
        static_cast< repeat_timer* >( arg )->callback( );
    }
} // namespace rule_composer::lib::util
