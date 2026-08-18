/**
 * \file set_color.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_SET_LIGHT_COLOR_HPP
#define RULE_COMPOSER_CMD_SET_LIGHT_COLOR_HPP

#include <cstdint>

#include <domain/rules/commands/command_interface.hpp>

namespace rule_composer::domain::rules::commands::light
{
    struct rgb_color
    {
        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;
    };

    class set_color : public command_interface
    {
    public:

        explicit set_color( const rgb_color& color );

        bool is_supported_by( entities::device& dev ) const override;

        [[nodiscard]]
        rgb_color get_color( ) const;

    private:

        rgb_color color;
    };

} // namespace rule_composer::domain::rules::commands::light

#endif // RULE_COMPOSER_CMD_SET_LIGHT_COLOR_HPP
