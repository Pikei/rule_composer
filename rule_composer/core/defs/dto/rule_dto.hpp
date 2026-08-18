/**
 * \file rule_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_RULE_DTO_HPP
#define RULE_COMPOSER_RULE_DTO_HPP

#include <memory>

#include <domain/id_types/id_types.hpp>
#include <dto/command_dto.hpp>
#include <dto/condition_dto.hpp>
namespace rule_composer::core::dto
{
    struct rule_dto
    {
        domain::id_types::rule_id                     id;
        condition_dto                                 condition;
        std::vector< std::shared_ptr< command_dto > > actions;
    };
} // namespace rule_composer::core::dto

#endif // RULE_COMPOSER_RULE_DTO_HPP
