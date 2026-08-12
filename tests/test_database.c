#include "unity/unity.h"
#include "stuman/database.h"

void setUp(void) {}

void tearDown(void) {}

static void test_database_create_success(void)
{
    Database* database = create_database();

    TEST_ASSERT_NOT_NULL(database);
    TEST_ASSERT_EQUAL_size_t(0, database->size);
    TEST_ASSERT_EQUAL_size_t(4, database->capacity);

    destroy_database(database);
}

static void test_database_destroy_null_safe(void)
{
    destroy_database(NULL);
}

static void test_database_add_students(void)
{
    Database* database = create_database();
    Gender gender = MALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", gender, "ul. Niszowa");

    TEST_ASSERT_TRUE(add_student(database, student));

    destroy_database(database);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_database_create_success);
    RUN_TEST(test_database_destroy_null_safe);
    RUN_TEST(test_database_add_students);
    return UNITY_END();
}