cmake_minimum_required(VERSION 3.16)

project(discord-to-md C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(discord-to-md
    src/main.c
)