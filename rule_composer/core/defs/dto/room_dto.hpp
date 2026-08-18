/**
 * \file room_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ROOM_DTO_HPP
#define RULE_COMPOSER_ROOM_DTO_HPP

#include <string>

#include <domain/id_types/id_types.hpp>
namespace rule_composer::core::dto
{
    struct room_dto
    {
        domain::id_types::room_id id;
        std::string               name;
    };
} // namespace rule_composer::core::dto

#endif // RULE_COMPOSER_ROOM_DTO_HPP
