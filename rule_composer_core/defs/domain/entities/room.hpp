/**
 * \file room.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_ROOM_HPP
#define RULE_COMPOSER_ROOM_HPP

#include <string>

#include <domain/id_types/id_types.hpp>

struct room
{
    room_id     id;
    std::string name;
};

#endif // RULE_COMPOSER_ROOM_HPP
