/**
 * @file database.h
 * @brief Defining the Database model and methods
 *
 * @defgroup STUMAN_MODEL_DATABASE Database Model
 * @ingroup STUMAN_MODEL
 *
 * REFERENCE:
 * - (TBD)
 *
 * ASSUMPTIONS AND LIMITATIONS:
 * - (TBD)
 *
 * @author kamil-klawi
 * @date 11/08/2026
 */

#ifndef DATABASE_H
#define DATABASE_H

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "student.h"

/******************************************************************************
 * Macro Definitions
 *****************************************************************************/

#define INITIAL_DATABASE_SIZE 0
#define INITIAL_DATABASE_CAPACITY 4
#define DEFAULT_DATABASE_FILENAME "student_db"
#define DEFAULT_DATABASE_BIN_PATH DEFAULT_DATABASE_FILENAME ".bin"
#define DEFAULT_DATABASE_JSON_PATH DEFAULT_DATABASE_FILENAME ".json"

/******************************************************************************
 * Type Definitions
 *****************************************************************************/

typedef struct {
    Student *students;
    size_t size;
    size_t capacity;
} Database;

/******************************************************************************
 * Exported Functions
 *****************************************************************************/

/** Database lifecycle */
Database* create_database(void);
void destroy_database(Database *database);

/** Students operations */
bool add_student(Database *database, const Student *student);
bool remove_student_by_id(Database *database, uint32_t id);
bool remove_student_by_pesel(Database *database, const char *pesel);
Student* find_student_by_id(const Database *database, uint32_t id);
Student* find_student_by_pesel(const Database *database, const char *pesel);
void display_all_students(const Database *database);
size_t display_database_size(const Database *database);

/** Files I/O operations */
void save_database_to_file(const Database *database, const char *path);
void open_database_from_file(Database *database, const char *path);
void save_database_to_json(const Database *database, const char *path);
void open_database_from_json(Database *database, const char *path);

#endif // DATABASE_H