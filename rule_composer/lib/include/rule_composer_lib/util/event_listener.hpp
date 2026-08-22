/**
 * \file event_listener.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_EVENT_LISTENER_HPP
#define RULE_COMPOSER_EVENT_LISTENER_HPP
#include <functional>

namespace rule_composer::lib::util
{
    template < typename T >
    class event_listener
    {
    public:

        virtual ~event_listener( ) = default;
        using callback_t           = std::function< void( const T& ) >;

        void add_event_listener( callback_t cb )
        {
            callbacks.push_back( std::move( cb ) );
        }

    protected:

        void notify( const T& event )
        {
            for ( const auto& cb : callbacks )
            {
                cb( event );
            }
        }

    private:

        std::vector< callback_t > callbacks;
    };

} // namespace rule_composer::lib::util

#endif // RULE_COMPOSER_EVENT_LISTENER_HPP
