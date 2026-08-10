/**
 * \file command_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMMAND_DTO_HPP
#define RULE_COMPOSER_COMMAND_DTO_HPP

#include <enums/action_type.hpp>

class command_dto
{
public:
    explicit command_dto(action_type type) : type(type) { }
    virtual ~command_dto() = default;

    [[nodiscard]]
    action_type get_type() const
    {
        return type;
    }

private:
    action_type type;
};

template <typename T>
class parametrised_command_dto : public command_dto
{
public:
    explicit parametrised_command_dto(action_type type, const T& value) : command_dto(type),
                                                                          value(value) { }
    const T& get_value() const
    {
        return value;
    }

private:
    T value;
};

#endif // RULE_COMPOSER_COMMAND_DTO_HPP
