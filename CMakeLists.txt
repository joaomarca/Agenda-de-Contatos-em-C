cmake_minimum_required(VERSION 3.10)

project(Agenda C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_library(agenda STATIC src/agenda.c)

add_executable(main src/main.c)

target_link_libraries(main PRIVATE agenda)