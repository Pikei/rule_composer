/**
 * \file command_dto.hpp
 * Created by Piotr Karol 2026
 */
#ifndef RULE_COMPOSER_COMMAND_DTO_HPP
#define RULE_COMPOSER_COMMAND_DTO_HPP

enum class action_type
{
    turn_on_light,
    turn_off_light,
    set_brightness,
    set_light_color,

    turn_on_socket,
    turn_off_socket,

    open_curtain,
    close_curtain,
    set_curtain_position
};

class command_dto
{
public:
    explicit command_dto(action_type type) : type(type) { }
    virtual ~command_dto() = default;
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
