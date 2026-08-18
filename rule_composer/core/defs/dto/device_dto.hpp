/**
 * \file device_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_DTO_HPP
#define RULE_COMPOSER_DEVICE_DTO_HPP

#include <optional>
#include <string>
#include <vector>

#include <domain/enums/device_feature.hpp>
#include <domain/enums/device_type.hpp>
#include <domain/id_types/id_types.hpp>
#include <dto/rule_dto.hpp>

namespace rule_composer::core::dto
{
    struct device_dto
    {
        domain::id_types::device_id                  id;
        std::string                                  name;
        domain::enums::device_type                   type;
        domain::id_types::room_id                    room;
        std::optional< domain::id_types::group_id >  group;
        std::vector< rule_dto >                      rules;
        std::vector< domain::enums::device_feature > features;
    };
} // namespace rule_composer::core::dto
#endif // RULE_COMPOSER_DEVICE_DTO_HPP
