/**
 * \file event_loop.cpp
 * Created by Piotr Karol 2026
 */

#include <csignal>

#include <app/event_loop.hpp>
#include <app/repeat_timer.hpp>
#include <spdlog/spdlog.h>

event_loop::event_loop( )
{
    base = event_base_new( );
    if ( !base )
    {
        throw std::runtime_error( "event_base_new failed" );
    }

    sigint_event = evsignal_new( base, SIGINT, &event_loop::on_signal, this );
    if ( !sigint_event || event_add( sigint_event, nullptr ) != 0 )
    {
        event_base_free( base );
        throw std::runtime_error( "failed to register SIGINT handler" );
    }

    sigterm_event = evsignal_new( base, SIGTERM, &event_loop::on_signal, this );
    if ( !sigterm_event || event_add( sigterm_event, nullptr ) != 0 )
    {
        event_free( sigint_event );
        event_base_free( base );
        throw std::runtime_error( "failed to register SIGTERM handler" );
    }
}

event_loop::~event_loop( )
{
    if ( sigint_event )
    {
        event_free( sigint_event );
    }
    if ( sigterm_event )
    {
        event_free( sigterm_event );
    }
    if ( base )
    {
        event_base_free( base );
    }
}

void event_loop::post( std::function< void( ) > task )
{
    auto* task_ptr = new std::function< void( ) >( std::move( task ) );
    if ( event_base_once( base, -1, EV_TIMEOUT, &event_loop::on_once, task_ptr, nullptr ) != 0 )
    {
        delete task_ptr;
        throw std::runtime_error( "event_base_once failed" );
    }
}

repeat_timer event_loop::create_repeat_timer( std::chrono::milliseconds interval, std::function< void( ) > callback )
{
    return repeat_timer { base, interval, std::move( callback ) };
}

timeout_timer event_loop::create_timeout_timer( std::function< void( ) > callback )
{
    return timeout_timer { base, std::move( callback ) };
}

void event_loop::run( )
{
    event_base_dispatch( base );
}

void event_loop::stop( )
{
    event_base_loopexit( base, nullptr );
}

void event_loop::on_once( evutil_socket_t, short, void* arg )
{
    auto* task_ptr = static_cast< std::function< void( ) >* >( arg );
          ( *task_ptr )( );
    delete task_ptr;
}

void event_loop::on_signal( evutil_socket_t signum, short, void* arg )
{
    auto* self = static_cast< event_loop* >( arg );
    self->stop( );
}
