/**
 * \file timeout_timer.cpp
 * Created by Piotr Karol 2026
 */

#include <stdexcept>

#include <app/timeout_timer.hpp>

timeout_timer::timeout_timer( event_base* base_, std::function< void( ) > callback_ ) : callback { std::move( callback_ ) }
{
    time_event = event_new( base_, -1, EV_TIMEOUT, &timeout_timer::on_timeout, this );
    if ( !time_event )
    {
        throw std::runtime_error( "event_new (timeout_timer) failed" );
    }
}

timeout_timer::~timeout_timer( )
{
    if ( time_event )
    {
        event_del( time_event );
        event_free( time_event );
    }
}

void timeout_timer::start( std::chrono::milliseconds delay )
{
    timeval tv { };
    tv.tv_sec  = static_cast< long >( delay.count( ) / 1000 );
    tv.tv_usec = static_cast< long >( ( delay.count( ) % 1000 ) * 1000 );
    event_add( time_event, &tv );
}

void timeout_timer::stop( )
{
    event_del( time_event );
}

void timeout_timer::on_timeout( evutil_socket_t, short, void* arg )
{
    static_cast< timeout_timer* >( arg )->callback( );
}
