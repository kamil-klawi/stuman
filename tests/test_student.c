#include "unity/unity.h"
#include "stuman/student.h"

void setUp(void) {}

void tearDown(void) {}

void test_student_create_success(void)
{
    Gender gender = MALE;
    Student *student = student_create(1, "John", "Mark", "12345678901", gender, "ul. Niszowa");

    TEST_ASSERT_NOT_NULL(student);
    TEST_ASSERT_EQUAL_UINT32(1, student->id);
    TEST_ASSERT_EQUAL_STRING("John", student->first_name);
    TEST_ASSERT_EQUAL_STRING("Mark", student->last_name);
    TEST_ASSERT_EQUAL(gender, student->gender);

    student_destroy(student);
}

void test_student_destroy_null_safe(void)
{
    student_destroy(NULL);
}

void test_student_create_null_arguments(void)
{
    Gender gender = MALE;
    Student *student = student_create(1, NULL, "Kowalski", "12345678901", gender, "ul. Wiejska 1");
    TEST_ASSERT_NULL(student);
    student_destroy(student);
}

void test_student_add_grade_valid_and_invalid_values(void)
{
    Gender gender = MALE;
    Student *student = student_create(1, "Jan", "Kowalski", "12345678901", gender, "ul. Wiejska 1");

    // Correct
    TEST_ASSERT_TRUE(student_add_grade(student, 2.0));
    TEST_ASSERT_TRUE(student_add_grade(student, 3.5));
    TEST_ASSERT_TRUE(student_add_grade(student, 5.0));

    // Incorrect
    TEST_ASSERT_FALSE(student_add_grade(student, 1.0));
    TEST_ASSERT_FALSE(student_add_grade(student, 6.0));
    TEST_ASSERT_FALSE(student_add_grade(student, -3.0));

    student_destroy(student);
}

void test_student_get_average_no_grades(void)
{
    Gender gender = MALE;
    Student *student = student_create(1, "Jan", "Kowalski", "12345678901", gender, "ul. Wiejska 1");

    TEST_ASSERT_TRUE(student_get_average_grade(student));

    student_destroy(student);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_student_create_success);
    RUN_TEST(test_student_destroy_null_safe);
    RUN_TEST(test_student_create_null_arguments);
    RUN_TEST(test_student_add_grade_valid_and_invalid_values);
    RUN_TEST(test_student_get_average_no_grades);
    return UNITY_END();
}