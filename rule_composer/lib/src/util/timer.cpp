/**
 * \file timer.cpp
 * Created by Piotr Karol 2026
 */

#include <stdexcept>
#include <utility>

#include <rule_composer_lib/util/timer.hpp>

namespace rule_composer::lib::util
{

    timer::timer( event* time_event_, std::chrono::milliseconds time_, std::function< void( ) > callback_ ) :
        time_event { time_event_ },
        chrono { time_ },
        callback { std::move( callback_ ) }
    {
        // time_event = event_new( loop_.get_event_base( ), -1, event_flag_, &timer::on_trigger, this );
        if ( !time_event )
        {
            throw std::runtime_error( "event_new (timeout_timer) failed" );
        }
    }

    timer::~timer( )
    {
        if ( time_event )
        {
            event_del( time_event );
            event_free( time_event );
        }
    }

    void timer::start( )
    {
        timeval tv { };
        tv.tv_sec  = static_cast< long >( chrono.count( ) / 1000 );
        tv.tv_usec = static_cast< long >( ( chrono.count( ) % 1000 ) * 1000 );
        event_add( time_event, &tv );
        running = true;
    }

    void timer::stop( )
    {
        if ( !running )
        {
            return;
        }

        event_del( time_event );
        running = false;
    }

    bool timer::is_running( ) const
    {
        return running;
    }

    void timer::set_chrono( const std::chrono::milliseconds chrono_ )
    {
        this->chrono = chrono_;
    }

    void timer::on_trigger( int fd, short events, void* arg )
    {
    }

} // namespace rule_composer::lib::util
