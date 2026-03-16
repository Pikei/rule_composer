set(APP_NAME "rule_composer_core")
set(BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/${APP_NAME}/config")

set(SOURCE_FILES
        src/app/main.cpp
        src/app/application.cpp
        src/app/app_options.cpp
)

add_executable(${APP_NAME} ${SOURCE_FILES})

target_include_directories(${APP_NAME} PRIVATE defs)

target_link_libraries(${APP_NAME} PRIVATE
        cxxopts
        spdlog
        nlohmann_json::nlohmann_json
)

message(STATUS "Copying config directory")
file(COPY ${CONFIG_DIR} DESTINATION ${BUILD_DIR})

