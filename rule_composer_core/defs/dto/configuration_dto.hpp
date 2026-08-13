/**
 * \file configuration_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_CONFIGURATION_DTO_HPP
#define RULE_COMPOSER_CONFIGURATION_DTO_HPP

#include <vector>

#include <dto/device_dto.hpp>
#include <dto/group_dto.hpp>
#include <dto/room_dto.hpp>

struct configuration_dto
{
    std::vector< room_dto >   rooms;
    std::vector< group_dto >  groups;
    std::vector< device_dto > devices;
};

#endif // RULE_COMPOSER_CONFIGURATION_DTO_HPP
