set(APP_NAME "rule_composer_core")
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/${APP_NAME}/config")

set(SOURCE_FILES
        src/app/main.cpp
        src/app/application.cpp
        src/app/app_options.cpp

        src/util/logger_creator.cpp

        src/domain/entities/device.cpp
        src/domain/rules/rule.cpp

        src/domain/rules/conditions/condition_group.cpp
        src/domain/rules/conditions/condition.cpp

        src/domain/rules/commands/light/cmd_turn_on_light.cpp
        src/domain/rules/commands/light/cmd_turn_off_light.cpp
        src/domain/rules/commands/light/cmd_set_brightness.cpp
        src/domain/rules/commands/light/cmd_set_light_color.cpp
        src/domain/rules/commands/curtains/cmd_open_curtain.cpp
        src/domain/rules/commands/curtains/cmd_close_curtain.cpp
        src/domain/rules/commands/curtains/cmd_set_position.cpp
        src/domain/rules/commands/socket/cmd_turn_on_socket.cpp
        src/domain/rules/commands/socket/cmd_turn_off_socket.cpp
        src/domain/rules/commands/thermostat/cmd_set_temperature.cpp

        src/util/json_utils.cpp
)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(${APP_NAME} ${SOURCE_FILES})

target_include_directories(${APP_NAME} PRIVATE defs defs/domain)

target_link_libraries(${APP_NAME} PRIVATE
        cxxopts
        spdlog
        nlohmann_json::nlohmann_json
        protobuf::libprotobuf
        gRPC::grpc++
)

message(STATUS "Copying config directory")
file(COPY ${CONFIG_DIR} DESTINATION ${BUILD_DIR})

message(STATUS "Setting compile definition: RUNTIME_CONFIG=${CONFIG_DIR}/config.json")
add_compile_definitions(RUNTIME_CONFIG="${CONFIG_DIR}/config.json")
message(STATUS "Setting compile definition: BINARY_CONFIG=${BUILD_DIR}/config/config.json")
add_compile_definitions(BINARY_CONFIG="${BUILD_DIR}/config/config.json")

if (TEST)
    add_subdirectory(test)
endif ()

