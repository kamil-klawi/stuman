cmake_minimum_required(VERSION 4.2.3)

project(stuman VERSION 0.1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SOURCES
    src/main.c
)

add_executable(stuman ${SOURCES})

target_include_directories(stuman PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    target_compile_options(stuman PRIVATE /W4 /WX)
else()
    target_compile_options(stuman PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wstrict-prototypes
        -Wmissing-prototypes
        -Wold-style-definition
        -Wnull-dereference
        -Wformat=2
    )
endif()

set_target_properties(stuman PROPERTIES COMPILE_WARNING_AS_ERROR ON)