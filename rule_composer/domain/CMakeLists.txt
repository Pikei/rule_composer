set(DOMAIN_NAME "rule_composer_domain")
set(DOMAIN_SRC
        src/entities/device.cpp

        src/rules/rule.cpp
        src/rules/context.cpp

        src/rules/conditions/condition_group.cpp
        src/rules/conditions/condition.cpp

        src/rules/commands/light/turn_on.cpp
        src/rules/commands/light/turn_off.cpp
        src/rules/commands/light/set_brightness.cpp
        src/rules/commands/light/set_color.cpp

        src/rules/commands/curtains/open.cpp
        src/rules/commands/curtains/close.cpp
        src/rules/commands/curtains/set_position.cpp

        src/rules/commands/socket/turn_on.cpp
        src/rules/commands/socket/turn_off.cpp

        src/rules/commands/thermostat/set_temperature.cpp
)

add_library(${DOMAIN_NAME} ${DOMAIN_SRC})
target_include_directories(${DOMAIN_NAME} PUBLIC include)