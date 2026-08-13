/**
 * \file repeat_timer.cpp
 * Created by Piotr Karol 2026
 */

#include <stdexcept>

#include <app/repeat_timer.hpp>

repeat_timer::repeat_timer( event_base* base_, std::chrono::milliseconds interval_, std::function< void( ) > callback_ ) :
    base { base_ },
    interval { interval_ },
    callback { std::move( callback_ ) }
{
    time_event = event_new( base_, -1, EV_PERSIST, &repeat_timer::on_repeat, this );
    if ( !time_event )
    {
        throw std::runtime_error( "event_new (repeat_timer) failed" );
    }
}

repeat_timer::~repeat_timer( )
{
    if ( time_event )
    {
        event_del( time_event );
        event_free( time_event );
    }
}

void repeat_timer::start( )
{
    timeval tv { };
    tv.tv_sec  = static_cast< long >( interval.count( ) / 1000 );
    tv.tv_usec = static_cast< long >( ( interval.count( ) % 1000 ) * 1000 );

    if ( event_add( time_event, &tv ) != 0 )
    {
        throw std::runtime_error( "event_add (repeat_timer) failed" );
    }
    running = true;
}

void repeat_timer::stop( )
{
    if ( !running )
    {
        return;
    }

    event_del( time_event );
    running = false;
}

bool repeat_timer::is_running( ) const
{
    return running;
}

void repeat_timer::on_repeat( evutil_socket_t, short, void* arg )
{
    static_cast< repeat_timer* >( arg )->callback( );
}
