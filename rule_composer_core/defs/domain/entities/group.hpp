/**
 * \file group.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_GROUP_HPP
#define RULE_COMPOSER_GROUP_HPP

#include <string>

#include <domain/id_types/id_types.hpp>

struct group
{
    group_id    id;
    std::string name;
};

#endif // RULE_COMPOSER_GROUP_HPP
