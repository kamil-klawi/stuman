cmake_minimum_required(VERSION 4.2.3)

project(stuman VERSION 0.1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SOURCES
    src/main.c
    src/student.c
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

# UNIT TESTS

enable_testing()

add_executable(unit_tests
    tests/test_student.c
    tests/unity/unity.c
    src/student.c
)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/unity
)

target_compile_options(unit_tests PRIVATE ${COMMON_COMPILE_OPTIONS})
set_target_properties(unit_tests PROPERTIES COMPILE_WARNING_AS_ERROR ON)

add_test(NAME StudentUnitTests COMMAND unit_tests)