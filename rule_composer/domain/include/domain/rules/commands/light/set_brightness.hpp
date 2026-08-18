/**
 * \file set_brightness.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_SET_BRIGHTNESS_HPP
#define RULE_COMPOSER_CMD_SET_BRIGHTNESS_HPP

#include <cstdint>

#include <domain/rules/commands/command_interface.hpp>

namespace rule_composer::domain::rules::commands::light
{
    class set_brightness : public command_interface
    {
    public:

        explicit set_brightness( std::uint8_t brightness );
        bool is_supported_by( entities::device& dev ) const override;

        [[nodiscard]]
        std::uint8_t get_brightness( ) const;

    private:

        std::uint8_t brightness;
    };

} // namespace rule_composer::domain::rules::commands::light

#endif // RULE_COMPOSER_CMD_SET_BRIGHTNESS_HPP
