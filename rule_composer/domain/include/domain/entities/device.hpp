/**
 * \file device.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_DEVICE_HPP
#define RULE_COMPOSER_DEVICE_HPP

#include <optional>
#include <string>
#include <vector>

#include <domain/enums/device_feature.hpp>
#include <domain/enums/device_type.hpp>
#include <domain/id_types/id_types.hpp>
#include <domain/rules/rule.hpp>

namespace rule_composer::domain::entities
{
    class device
    {
    public:

        explicit device( id_types::device_id                 id,
                         std::string                         name,
                         enums::device_type                  type,
                         id_types::room_id                   room,
                         std::optional< id_types::group_id > group = std::nullopt );

        void add_rule( rules::rule new_rule );

        [[nodiscard]]
        id_types::device_id get_id( ) const;

        [[nodiscard]]
        const std::string& get_name( ) const;

        [[nodiscard]]
        enums::device_type get_type( ) const;

        [[nodiscard]]
        id_types::room_id get_room_id( ) const;

        [[nodiscard]]
        std::optional< id_types::group_id > get_group( ) const;

        [[nodiscard]]
        const std::vector< rules::rule >& get_rules( ) const;

        [[nodiscard]]
        const std::vector< enums::device_feature >& get_features( ) const;

        bool has_feature( enums::device_feature feature );

    private:

        id_types::device_id                  id;
        std::string                          name;
        enums::device_type                   type;
        id_types::room_id                    room;
        std::optional< id_types::group_id >  group;
        std::vector< rules::rule >           rules;
        std::vector< enums::device_feature > features;
    };
} // namespace rule_composer::domain::entities

#endif // RULE_COMPOSER_DEVICE_HPP
