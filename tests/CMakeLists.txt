add_library(unity STATIC unity/unity.c)
target_include_directories(unity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/unity)

function(add_unit_test TEST_NAME TEST_SRC)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} PRIVATE stuman_lib unity)
    target_compile_options(${TEST_NAME} PRIVATE ${COMMON_COMPILE_OPTIONS})
    set_target_properties(${TEST_NAME} PROPERTIES COMPILE_WARNING_AS_ERROR ON)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

add_unit_test(StudentUnitTests test_student.c)
add_unit_test(DatabaseUnitTests test_database.c)