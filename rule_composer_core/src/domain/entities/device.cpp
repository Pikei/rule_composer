/**
 * \file device.cpp
 * Created by Piotr Karol 2026
 */

#include <algorithm>
#include <entities/device.hpp>
#include <utility>

device::device(device_id id, std::string name, device_type type, room_id room, std::optional<group_id> group) :
    id { id },
    name { std::move(name) },
    type { type },
    room { room }
{
    if (group.has_value())
    {
        this->group = group.value();
    }
}


void device::add_rule(rule& new_rule)
{
    for (const auto& action : new_rule)
    {
        if (!action->is_supported_by(*this))
        {
            return;
        }
    }

    rules.push_back(std::move(new_rule));
}

device_id device::get_id() const
{
    return id;
}

const std::string& device::get_name() const
{
    return name;
}

device_type device::get_type() const
{
    return type;
}

room_id device::get_room_id() const
{
    return room;
}

std::optional<group_id> device::get_group() const
{
    return group;
}

const std::vector<rule>& device::get_rules() const
{
    return rules;
}

const std::vector<device_feature>& device::get_features() const
{
    return features;
}

bool device::has_feature(device_feature feature)
{
    return std::any_of(features.begin(), features.end(), [feature](const auto& f)
                       { return f == feature; });
}