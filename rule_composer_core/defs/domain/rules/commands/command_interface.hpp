/**
 * \file command_interface.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMMAND_INTERFACE_HPP
#define RULE_COMPOSER_COMMAND_INTERFACE_HPP

class device;

class command_interface
{
public:

    virtual ~command_interface( ) = default;

    virtual bool is_supported_by( device& dev ) const = 0;
};

#endif // RULE_COMPOSER_COMMAND_INTERFACE_HPP
