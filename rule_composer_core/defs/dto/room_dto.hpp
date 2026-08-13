/**
 * \file room_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ROOM_DTO_HPP
#define RULE_COMPOSER_ROOM_DTO_HPP

#include <string>

#include <id_types/id_types.hpp>

struct room_dto
{
    room_id     id;
    std::string name;
};

#endif // RULE_COMPOSER_ROOM_DTO_HPP
