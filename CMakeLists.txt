cmake_minimum_required(VERSION 4.2.3)

project(stuman VERSION 0.3.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    set(COMMON_COMPILE_OPTIONS /W4 /WX)
else()
    set(COMMON_COMPILE_OPTIONS
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

add_library(stuman_lib STATIC
    src/student.c
    src/database.c
)

target_include_directories(stuman_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(stuman_lib PRIVATE ${COMMON_COMPILE_OPTIONS})
set_target_properties(stuman_lib PROPERTIES COMPILE_WARNING_AS_ERROR ON)

add_executable(stuman src/main.c)
target_link_libraries(stuman PRIVATE stuman_lib)
target_compile_options(stuman PRIVATE ${COMMON_COMPILE_OPTIONS})
set_target_properties(stuman PROPERTIES COMPILE_WARNING_AS_ERROR ON)

# UNIT TESTS
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()