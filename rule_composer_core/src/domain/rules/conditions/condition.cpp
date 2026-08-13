/**
 * \file condition.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/conditions/condition.hpp>

condition::condition( const condition_type type, const comparison_operator comparison, const condition_value value ) :
    type { type },
    comparison { comparison },
    value { value }
{
}

bool condition::evaluate( const context& ctx ) const
{
    if ( type == condition_type::time )
    {
        return evaluate_time( ctx );
    }
    if ( type == condition_type::weekday )
    {
        return evaluate_weekday( ctx );
    }
    if ( type == condition_type::temperature )
    {
        return evaluate_temperature( ctx );
    }
    return false;
}

condition_type condition::get_type( ) const
{
    return type;
}

comparison_operator condition::get_comparison( ) const
{
    return comparison;
}

condition_value condition::get_value( ) const
{
    return value;
}

bool condition::evaluate_time( const context& ctx ) const
{
    switch ( comparison )
    {
        case comparison_operator::equal:
            return ctx.get_current_time( ) == std::get< std::chrono::minutes >( value );
        case comparison_operator::not_equal:
            return ctx.get_current_time( ) != std::get< std::chrono::minutes >( value );
        case comparison_operator::greater:
            return ctx.get_current_time( ) > std::get< std::chrono::minutes >( value );
        case comparison_operator::greater_equal:
            return ctx.get_current_time( ) >= std::get< std::chrono::minutes >( value );
        case comparison_operator::less:
            return ctx.get_current_time( ) < std::get< std::chrono::minutes >( value );
        case comparison_operator::less_equal:
            return ctx.get_current_time( ) <= std::get< std::chrono::minutes >( value );
        default:
            return false;
    }
}

bool condition::evaluate_weekday( const context& ctx ) const
{
    auto condition_weekday = static_cast< std::uint8_t >( std::get< weekday >( value ) );
    auto context_weekday   = static_cast< std::uint8_t >( ctx.get_weekday( ) );

    switch ( comparison )
    {
        case comparison_operator::equal:
            return condition_weekday == context_weekday;
        case comparison_operator::not_equal:
            return condition_weekday != context_weekday;
        case comparison_operator::greater:
            return condition_weekday > context_weekday;
        case comparison_operator::greater_equal:
            return condition_weekday >= context_weekday;
        case comparison_operator::less:
            return condition_weekday < context_weekday;
        case comparison_operator::less_equal:
            return condition_weekday <= context_weekday;
        default:
            return false;
    }

    return std::get< weekday >( value ) == ctx.get_weekday( );
}

bool condition::evaluate_temperature( const context& ctx ) const
{
    switch ( comparison )
    {
        case comparison_operator::equal:
            return std::get< double >( value ) == ctx.get_temperature( );
        case comparison_operator::not_equal:
            return std::get< double >( value ) != ctx.get_temperature( );
        case comparison_operator::greater:
            return std::get< double >( value ) > ctx.get_temperature( );
        case comparison_operator::greater_equal:
            return std::get< double >( value ) >= ctx.get_temperature( );
        case comparison_operator::less:
            return std::get< double >( value ) < ctx.get_temperature( );
        case comparison_operator::less_equal:
            return std::get< double >( value ) <= ctx.get_temperature( );
        default:
            return false;
    }
}
