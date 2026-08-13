/**
 * \file device_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_DTO_HPP
#define RULE_COMPOSER_DEVICE_DTO_HPP

#include <optional>
#include <string>
#include <vector>

#include <dto/rule_dto.hpp>
#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <id_types/id_types.hpp>

struct device_dto
{
    device_id                     id;
    std::string                   name;
    device_type                   type;
    room_id                       room;
    std::optional< group_id >     group;
    std::vector< rule_dto >       rules;
    std::vector< device_feature > features;
};

#endif // RULE_COMPOSER_DEVICE_DTO_HPP
