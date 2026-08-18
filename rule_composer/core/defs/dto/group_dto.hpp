/**
 * \file group_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_GROUP_DTO_HPP
#define RULE_COMPOSER_GROUP_DTO_HPP

#include <string>

#include <domain/id_types/id_types.hpp>
namespace rule_composer::core::dto
{
    struct group_dto
    {
        domain::id_types::group_id id;
        std::string                name;
    };
} // namespace rule_composer::core::dto

#endif // RULE_COMPOSER_GROUP_DTO_HPP
