/**
 * @file student.h
 * @brief Defining the Student model and methods
 *
 * @defgroup STUMAN_MODEL_STUDENT Student Model
 * @ingroup STUMAN_MODEL
 *
 * REFERENCE:
 * - (TBD)
 *
 * ASSUMPTIONS AND LIMITATIONS:
 * - (TBD)
 *
 * @author kamil-klawi
 * @date 09/08/2026
 */

#ifndef STUDENT_H
#define STUDENT_H

/******************************************************************************
 * Includes
 *****************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/******************************************************************************
 * Macro Definitions
 *****************************************************************************/

#define NAME_LENGTH 40
#define PESEL_LENGTH 12 /**< \brief 11 digits and `\0` */
#define ADDRESS_LENGTH 100
#define INITIAL_GRADES_CAPACITY 4
#define INITIAL_GRADES_COUNT 0
#define INITIAL_GRADES_AVG 0.0

/******************************************************************************
 * Type Definitions
 *****************************************************************************/

typedef enum {
    MALE,
    FEMALE,
    UNKNOWN,
} Gender;

typedef struct {
    uint32_t id;
    char first_name[NAME_LENGTH];
    char last_name[NAME_LENGTH];
    char pesel[PESEL_LENGTH];
    char address[ADDRESS_LENGTH];
    Gender gender;

    double *grades;
    double grades_avg;
    size_t grades_count;
    size_t grades_capacity;
} Student;

/******************************************************************************
 * Exported Functions
 *****************************************************************************/

/** Student lifecycle */
Student* student_create(
    uint32_t id,
    const char *first_name,
    const char *last_name,
    const char *pesel,
    Gender gender,
    const char *address
);
void student_destroy(Student *student);

/** Student operations */
bool student_add_grade(Student *student, double grade);
bool student_get_average_grade(Student *student);
void display_student_details(const Student *student);

/** Conversion helpers */
const char* student_gender_to_string(Gender gender);
Gender student_gender_from_string(const char *str);

#endif // STUDENT_H