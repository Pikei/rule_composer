/**
 * \file cmd_set_light_color.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_SET_LIGHT_COLOR_HPP
#define RULE_COMPOSER_CMD_SET_LIGHT_COLOR_HPP

#include <cstdint>
#include <rules/commands/command_interface.hpp>

struct rgb_color
{
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
};

namespace command::light
{
    class cmd_set_light_color : public command_interface
    {
    public:
        explicit cmd_set_light_color(const rgb_color& color);

        bool is_supported_by(device& dev) const override;

        [[nodiscard]]
        rgb_color get_color() const;


    private:
        rgb_color color;
    };

} // command::light

#endif // RULE_COMPOSER_CMD_SET_LIGHT_COLOR_HPP
