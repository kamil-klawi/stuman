#include <stdio.h>
#include <stdlib.h>
#include "stuman/database.h"

/**
 * @brief Creates a new Database object
 *
 * @param[in] students Database students array
 * @param[in] size     Database size
 * @param[in] capacity Database capacity
 *
 * @return Pointer to the newly allocated Database object
 */
Database* create_database(void)
{
    Database *database = malloc(sizeof(Database));
    if (!database)
    {
        return NULL;
    }

    database->size = INITIAL_DATABASE_SIZE;
    database->capacity = INITIAL_DATABASE_CAPACITY;
    database->students = (Student *)malloc(database->capacity * sizeof(Student));

    if(!database->students)
    {
        free(database);
        return NULL;
    }

    return database;
}

/**
 * @brief Frees all memory allocated for a database
 *
 * @param[in,out] database Pointer to the Database structure to be deallocated
 */
void destroy_database(Database *database)
{
    if (!database)
    {
        return;
    }

    free(database->students);
    free(database);
}

/**
 * @brief Adds a student to the database record
 *
 * @param[in,out] database Pointer to the Database structure
 * @param[in]     student  The student object to be added
 *
 * @return True if the student was added successfully, false otherwise
 */
bool add_student(Database *database, const Student *student)
{
    if (!database || !student) {
        return false;
    }

    if (database->size == database->capacity) {
        size_t new_capacity = database->capacity * 2;

        Student *new_students = realloc(database->students, new_capacity * sizeof(Student));
        if (!new_students) {
            return false;
        }

        database->students = new_students;
        database->capacity = new_capacity;
    }

    database->students[database->size] = *student;
    database->size++;

    return true;
}