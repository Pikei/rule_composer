/**
 * \file rule_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_RULE_DTO_HPP
#define RULE_COMPOSER_RULE_DTO_HPP

#include <dto/command_dto.hpp>
#include <dto/condition_dto.hpp>
#include <id_types/id_types.hpp>
#include <memory>

struct rule_dto
{
    rule_id                                   id;
    condition_dto                             condition;
    std::vector<std::unique_ptr<command_dto>> actions;
};

#endif // RULE_COMPOSER_RULE_DTO_HPP
