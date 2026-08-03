/**
 * \file cmd_turn_on_socket.cpp
 * Created by Piotr Karol 2026
 */
#include <entities/device.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <rules/commands/socket/cmd_turn_on_socket.hpp>

namespace command::socket
{
    bool cmd_turn_on_socket::is_supported_by(device& dev) const
    {
        return dev.has_feature(device_feature::switchable) && (device_type::electric_socket == dev.get_type());
    }
} // command::socket
