set(APP_NAME "rule_composer_core")
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/rule_composer/core/config")

set(SOURCE_FILES
        src/app/main.cpp
        src/app/core_app.cpp
        src/app/app_options.cpp
        src/app/rule_engine.cpp

        src/util/config_parser.cpp
        src/util/domain_factory.cpp

)

find_package(protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_executable(${APP_NAME} ${SOURCE_FILES})

target_include_directories(${APP_NAME} PRIVATE defs defs/domain)

target_link_libraries(${APP_NAME} PRIVATE
        rule_composer_lib
        rule_composer_domain
        PahoMqttCpp::paho-mqttpp3
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

