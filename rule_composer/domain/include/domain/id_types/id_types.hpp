/**
 * \file id_types.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ID_TYPES_HPP
#define RULE_COMPOSER_ID_TYPES_HPP

#include <cstdint>

namespace rule_composer::domain::id_types
{
    using device_id = std::uint16_t;
    using room_id   = std::uint16_t;
    using group_id  = std::uint16_t;
    using rule_id   = std::uint16_t;
} // namespace rule_composer::domain::id_types

#endif // RULE_COMPOSER_ID_TYPES_HPP
