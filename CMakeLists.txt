cmake_minimum_required(VERSION 3.16)

project(discord-to-md C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    cjson
    GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
    GIT_TAG v1.7.19
)

FetchContent_MakeAvailable(cjson)

add_executable(discord-to-md
    src/main.c
    src/json_loader.c
)

target_include_directories(discord-to-md PRIVATE
    ${cjson_SOURCE_DIR}
)

target_link_libraries(discord-to-md PRIVATE cjson)