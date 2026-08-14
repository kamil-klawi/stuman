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

static void test_database_remove_student_by_id(void)
{
    Database* database = create_database();
    Gender gender = MALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", gender, "ul. Niszowa");

    TEST_ASSERT_TRUE(add_student(database, student));
    TEST_ASSERT_TRUE(remove_student_by_id(database, student->id));

    destroy_database(database);
}

static void test_database_remove_student_by_pesel(void)
{
    Database* database = create_database();
    Gender gender = MALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", gender, "ul. Niszowa");

    TEST_ASSERT_TRUE(add_student(database, student));
    TEST_ASSERT_TRUE(remove_student_by_pesel(database, student->pesel));

    destroy_database(database);
}

static void test_database_find_student_by_id(void)
{
    Database* database = create_database();
    Gender gender = MALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", gender, "ul. Niszowa");

    TEST_ASSERT_TRUE(add_student(database, student));
    TEST_ASSERT_NOT_NULL(find_student_by_id(database, student->id));
    TEST_ASSERT_TRUE(remove_student_by_pesel(database, student->pesel));

    destroy_database(database);
}

static void test_database_find_student_by_pesel(void)
{
    Database* database = create_database();
    Gender gender = MALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", gender, "ul. Niszowa");

    TEST_ASSERT_TRUE(add_student(database, student));
    TEST_ASSERT_NOT_NULL(find_student_by_pesel(database, student->pesel));
    TEST_ASSERT_TRUE(remove_student_by_id(database, student->id));

    destroy_database(database);
}

static void test_database_display_all_students(void)
{
    Database* database = create_database();
    Gender male = MALE;
    Gender female = FEMALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", male, "ul. Niszowa");
    Student* student1 = student_create(2, "Emily", "Mark", "12345678901", female, "ul. Niszowa");
    Student* student2 = student_create(3, "Steve", "Mark", "12345678901", male, "ul. Niszowa");

    add_student(database, student);
    add_student(database, student1);
    add_student(database, student2);

    display_all_students(database);

    destroy_database(database);
}

static void test_database_display_database_size(void)
{
    Database* database = create_database();
    Gender male = MALE;
    Gender female = FEMALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", male, "ul. Niszowa");
    Student* student1 = student_create(2, "Emily", "Mark", "12345678901", female, "ul. Niszowa");
    Student* student2 = student_create(3, "Steve", "Mark", "12345678901", male, "ul. Niszowa");

    add_student(database, student);
    add_student(database, student1);
    add_student(database, student2);

    TEST_ASSERT_EQUAL_size_t(3, display_database_size(database));

    destroy_database(database);
}

static void test_save_database_to_file(void)
{
    Database* database = create_database();
    Gender male = MALE;
    Gender female = FEMALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", male, "ul. Niszowa");
    Student* student1 = student_create(2, "Emily", "Mark", "12345678901", female, "ul. Niszowa");
    Student* student2 = student_create(3, "Steve", "Mark", "12345678901", male, "ul. Niszowa");

    add_student(database, student);
    add_student(database, student1);
    add_student(database, student2);

    save_database_to_file(database, DEFAULT_DATABASE_BIN_PATH);

    destroy_database(database);
}

static void test_save_and_open_empty_database(void)
{
    Database* database = create_database();
    save_database_to_file(database, DEFAULT_DATABASE_BIN_PATH);
    open_database_from_file(database, DEFAULT_DATABASE_BIN_PATH);

    TEST_ASSERT_EQUAL_UINT(0, database->size);
    destroy_database(database);
}

static void test_save_and_open_database(void)
{
    Database* database = create_database();
    Gender male = MALE;
    Gender female = FEMALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", male, "ul. Niszowa");
    Student* student1 = student_create(2, "Emily", "Mark", "12345678901", female, "ul. Niszowa");
    Student* student2 = student_create(3, "Steve", "Mark", "12345678901", male, "ul. Niszowa");

    add_student(database, student);
    add_student(database, student1);
    add_student(database, student2);

    save_database_to_file(database, DEFAULT_DATABASE_BIN_PATH);
    open_database_from_file(database, DEFAULT_DATABASE_BIN_PATH);

    TEST_ASSERT_EQUAL_UINT(3, database->size);

    destroy_database(database);
}

static void test_save_json_null_parameters(void)
{
    Database* database = create_database();
    save_database_to_json(NULL, "non_existent_file_12345.json");
    save_database_to_json(database, NULL);
}

static void test_save_database_to_json(void)
{
        Database* database = create_database();
    Gender male = MALE;
    Gender female = FEMALE;
    Student* student = student_create(1, "John", "Mark", "12345678901", male, "ul. Niszowa");
    Student* student1 = student_create(2, "Emily", "Mark", "12345678901", female, "ul. Niszowa");
    Student* student2 = student_create(3, "Steve", "Mark", "12345678901", male, "ul. Niszowa");

    add_student(database, student);
    add_student(database, student1);
    add_student(database, student2);

    save_database_to_json(database, DEFAULT_DATABASE_JSON_PATH);

    destroy_database(database);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_database_create_success);
    RUN_TEST(test_database_destroy_null_safe);
    RUN_TEST(test_database_add_students);
    RUN_TEST(test_database_remove_student_by_id);
    RUN_TEST(test_database_remove_student_by_pesel);
    RUN_TEST(test_database_find_student_by_id);
    RUN_TEST(test_database_find_student_by_pesel);
    RUN_TEST(test_database_display_all_students);
    RUN_TEST(test_database_display_database_size);
    RUN_TEST(test_save_database_to_file);
    RUN_TEST(test_save_and_open_empty_database);
    RUN_TEST(test_save_and_open_database);
    RUN_TEST(test_save_json_null_parameters);
    RUN_TEST(test_save_database_to_json);
    return UNITY_END();
}