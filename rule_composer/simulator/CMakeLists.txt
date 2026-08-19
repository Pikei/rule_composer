set(SIM_NAME "rule_composer_simulator")
set(SIM_SRC
        src/main.cpp
        src/sim_options.cpp
        src/sim_app.cpp
)

add_executable(${SIM_NAME} ${SIM_SRC})

target_include_directories(${SIM_NAME} PRIVATE defs)
target_link_libraries(${SIM_NAME} PRIVATE
        rule_composer_lib
        rule_composer_domain
        PahoMqttCpp::paho-mqttpp3
)

