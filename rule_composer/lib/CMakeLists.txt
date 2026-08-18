set(LIB_NAME "rule_composer_lib")
set(LIB_SRC
        src/app/application.cpp
        src/app/app_options.cpp

        src/util/event_loop.cpp
        src/util/timer.cpp
        src/util/timeout_timer.cpp
        src/util/repeat_timer.cpp
        src/util/json_utils.cpp
)

add_library(${LIB_NAME} ${LIB_SRC})
target_include_directories(${LIB_NAME} PUBLIC include)

target_link_libraries(${LIB_NAME} PUBLIC
        cxxopts
        spdlog
        nlohmann_json::nlohmann_json
        event_core
)