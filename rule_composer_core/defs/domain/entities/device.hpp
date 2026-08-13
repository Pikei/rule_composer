/**
 * \file device.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_HPP
#define RULE_COMPOSER_DEVICE_HPP

#include <optional>
#include <string>
#include <vector>

#include <enums/device_feature.hpp>
#include <enums/device_type.hpp>
#include <rules/rule.hpp>

class device
{
public:

    explicit device( device_id id, std::string name, device_type type, room_id room, std::optional< group_id > group = std::nullopt );

    void add_rule( rule new_rule );

    [[nodiscard]]
    device_id get_id( ) const;

    [[nodiscard]]
    const std::string& get_name( ) const;

    [[nodiscard]]
    device_type get_type( ) const;

    [[nodiscard]]
    room_id get_room_id( ) const;

    [[nodiscard]]
    std::optional< group_id > get_group( ) const;

    [[nodiscard]]
    const std::vector< rule >& get_rules( ) const;

    [[nodiscard]]
    const std::vector< device_feature >& get_features( ) const;

    bool has_feature( device_feature feature );

private:

    device_id                     id;
    std::string                   name;
    device_type                   type;
    room_id                       room;
    std::optional< group_id >     group;
    std::vector< rule >           rules;
    std::vector< device_feature > features;
};

#endif // RULE_COMPOSER_DEVICE_HPP
