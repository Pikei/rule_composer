/**
 * \file condition.cpp
 * Created by Piotr Karol 2026
 */

#include <domain/rules/conditions/condition.hpp>
#include <domain/rules/context.hpp>

namespace rule_composer::domain::rules::conditions
{
    condition::condition( const enums::condition_type type, const enums::comparison_operator comparison, const condition_value value ) :
        type { type },
        comparison { comparison },
        value { value }
    {
    }

    bool condition::evaluate( const context_interface& ctx ) const
    {
        if ( type == enums::condition_type::time )
        {
            return evaluate_time( ctx );
        }
        if ( type == enums::condition_type::weekday )
        {
            return evaluate_weekday( ctx );
        }
        if ( type == enums::condition_type::temperature )
        {
            return evaluate_temperature( ctx );
        }
        if ( type == enums::condition_type::humidity )
        {
            return evaluate_humidity( ctx );
        }
        return false;
    }

    enums::condition_type condition::get_type( ) const
    {
        return type;
    }

    enums::comparison_operator condition::get_comparison( ) const
    {
        return comparison;
    }

    condition_value condition::get_value( ) const
    {
        return value;
    }

    bool condition::evaluate_time( const context_interface& ctx ) const
    {
        switch ( comparison )
        {
            case enums::comparison_operator::equal:
                return ctx.get_current_time( ) == std::get< std::chrono::minutes >( value );
            case enums::comparison_operator::not_equal:
                return ctx.get_current_time( ) != std::get< std::chrono::minutes >( value );
            case enums::comparison_operator::greater:
                return ctx.get_current_time( ) > std::get< std::chrono::minutes >( value );
            case enums::comparison_operator::greater_equal:
                return ctx.get_current_time( ) >= std::get< std::chrono::minutes >( value );
            case enums::comparison_operator::less:
                return ctx.get_current_time( ) < std::get< std::chrono::minutes >( value );
            case enums::comparison_operator::less_equal:
                return ctx.get_current_time( ) <= std::get< std::chrono::minutes >( value );
            default:
                return false;
        }
    }

    bool condition::evaluate_weekday( const context_interface& ctx ) const
    {
        auto condition_weekday = static_cast< std::uint8_t >( std::get< enums::weekday >( value ) );
        auto context_weekday   = static_cast< std::uint8_t >( ctx.get_weekday( ) );

        switch ( comparison )
        {
            case enums::comparison_operator::equal:
                return condition_weekday == context_weekday;
            case enums::comparison_operator::not_equal:
                return condition_weekday != context_weekday;
            case enums::comparison_operator::greater:
                return condition_weekday > context_weekday;
            case enums::comparison_operator::greater_equal:
                return condition_weekday >= context_weekday;
            case enums::comparison_operator::less:
                return condition_weekday < context_weekday;
            case enums::comparison_operator::less_equal:
                return condition_weekday <= context_weekday;
            default:
                return false;
        }
    }

    bool condition::evaluate_temperature( const context_interface& ctx ) const
    {
        switch ( comparison )
        {
            case enums::comparison_operator::equal:
                return std::get< double >( value ) == ctx.get_temperature( );
            case enums::comparison_operator::not_equal:
                return std::get< double >( value ) != ctx.get_temperature( );
            case enums::comparison_operator::greater:
                return std::get< double >( value ) > ctx.get_temperature( );
            case enums::comparison_operator::greater_equal:
                return std::get< double >( value ) >= ctx.get_temperature( );
            case enums::comparison_operator::less:
                return std::get< double >( value ) < ctx.get_temperature( );
            case enums::comparison_operator::less_equal:
                return std::get< double >( value ) <= ctx.get_temperature( );
            default:
                return false;
        }
    }

    bool condition::evaluate_humidity( const context_interface& ctx ) const
    {
        switch ( comparison )
        {
            case enums::comparison_operator::equal:
                return std::get< double >( value ) == ctx.get_humidity( );
            case enums::comparison_operator::not_equal:
                return std::get< double >( value ) != ctx.get_humidity( );
            case enums::comparison_operator::greater:
                return std::get< double >( value ) > ctx.get_humidity( );
            case enums::comparison_operator::greater_equal:
                return std::get< double >( value ) >= ctx.get_humidity( );
            case enums::comparison_operator::less:
                return std::get< double >( value ) < ctx.get_humidity( );
            case enums::comparison_operator::less_equal:
                return std::get< double >( value ) <= ctx.get_humidity( );
            default:
                return false;
        }
    }
} // namespace rule_composer::domain::rules::conditions
