/**
 * \file cmd_set_position.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_SET_POSITION_HPP
#define RULE_COMPOSER_CMD_SET_POSITION_HPP

#include <cstdint>
#include <rules/commands/command_interface.hpp>

namespace command::curtain
{
    class cmd_set_position : public command_interface
    {
    public:
        explicit cmd_set_position(std::uint8_t position);
        bool is_supported_by(device& dev) const override;

    private:
        std::uint8_t                  position;
        static constexpr std::uint8_t max_position = 100;
    };

} // command::curtain

#endif // RULE_COMPOSER_CMD_SET_POSITION_HPP
