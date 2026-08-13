/**
 * \file cmd_turn_off_socket.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CMD_TURN_OFF_SOCKET_HPP
#define RULE_COMPOSER_CMD_TURN_OFF_SOCKET_HPP

#include <rules/commands/command_interface.hpp>

namespace command::socket
{
    class cmd_turn_off_socket : public command_interface
    {
    public:

        bool is_supported_by( device& dev ) const override;
    };

} // namespace command::socket

#endif // RULE_COMPOSER_CMD_TURN_OFF_SOCKET_HPP
