/**
 * \file command_interface.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMMAND_INTERFACE_HPP
#define RULE_COMPOSER_COMMAND_INTERFACE_HPP

namespace rule_composer::domain::entities
{
    class device;
}
namespace rule_composer::domain::rules
{
    class command_interface
    {
    public:

        virtual ~command_interface( ) = default;

        virtual bool is_supported_by( entities::device& dev ) const = 0;
    };
} // namespace rule_composer::domain::rules

#endif // RULE_COMPOSER_COMMAND_INTERFACE_HPP
