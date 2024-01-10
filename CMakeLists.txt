cmake_minimum_required(VERSION 3.28)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(deproj LANGUAGES CXX)

file(GLOB DEPROJ_SOURCE_FILES src/*.cpp)
file(GLOB DEPROJ_HEADER_FILES src/*.h)

add_executable(deproj
    ${DEPROJ_HEADER_FILES}
    ${DEPROJ_SOURCE_FILES}
)

set_target_properties(deproj
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(deproj
    PRIVATE
    ${deproj_SOURCE_DIR}/lib
)
