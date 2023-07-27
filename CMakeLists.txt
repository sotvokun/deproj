cmake_minimum_required(VERSION 3.18)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(tmplt LANGUAGES CXX)

file(GLOB TMPLT_SOURCE_FILES src/*.cpp)
file(GLOB TMPLT_HEADER_FILES src/*.h)

add_executable(
    tmplt
    ${TMPLT_SOURCE_FILES}
    ${TMPLT_HEADER_FILES}
)

target_include_directories(
    tmplt
    PRIVATE
    ${tmplt_SOURCE_DIR}/lib
)

set_target_properties(
    tmplt
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
    target_compile_options(
        tmplt
        PRIVATE
        /W4
        /permissive-
    )
else()
    target_compile_options(
        tmplt
        PRIVATE
        -Wall -Wextra -pedantic -pedantic-errors -Werror
    )
endif()
