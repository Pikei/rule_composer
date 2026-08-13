/**
 * \file cmd_set_brightness.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_SET_BRIGHTNESS_HPP
#define RULE_COMPOSER_CMD_SET_BRIGHTNESS_HPP

#include <cstdint>

#include <rules/commands/command_interface.hpp>

namespace command::light
{
    class cmd_set_brightness : public command_interface
    {
    public:

        explicit cmd_set_brightness( std::uint8_t brightness );
        bool is_supported_by( device& dev ) const override;

        [[nodiscard]]
        std::uint8_t get_brightness( ) const;

    private:

        std::uint8_t brightness;
    };

} // namespace command::light

#endif // RULE_COMPOSER_CMD_SET_BRIGHTNESS_HPP
