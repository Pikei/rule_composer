/**
 * \file room.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ROOM_HPP
#define RULE_COMPOSER_ROOM_HPP

#include <domain/id_types/id_types.hpp>
#include <string>

struct room
{
    room_id     id;
    std::string name;
};

#endif // RULE_COMPOSER_ROOM_HPP
