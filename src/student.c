#include <stdio.h>
#include <stdlib.h>
#include "stuman/student.h"

/**
 * @brief Creates a new Student object
 *
 * @param[in] id         Unique student identifier
 * @param[in] first_name Student's first name
 * @param[in] last_name  Student's last name
 * @param[in] pesel      PESEL
 * @param[in] gender     Gender value enum
 * @param[in] address    Student's residential address
 *
 * @return Pointer to the newly allocated Student object
 */
Student* student_create(
    uint32_t id,
    const char *first_name,
    const char *last_name,
    const char *pesel,
    Gender gender,
    const char *address
)
{
    Student* student = malloc(sizeof(Student));

    if(!student)
    {
        return NULL;
    }

    student->id = id;
    student->gender = gender;

    snprintf(student->first_name, NAME_LENGTH, "%s", first_name ? first_name : "");
    snprintf(student->last_name, NAME_LENGTH, "%s", last_name ? last_name : "");
    snprintf(student->pesel, PESEL_LENGTH, "%s", pesel ? pesel : "");
    snprintf(student->address, ADDRESS_LENGTH, "%s", address ? address : "");

    student->grades_capacity = INITIAL_GRADES_CAPACITY;
    student->grades_count = INITIAL_GRADES_COUNT;
    student->grades_avg = INITIAL_GRADES_AVG;
    student->grades = malloc(sizeof(*student->grades) * student->grades_capacity);

    if(!student->grades)
    {
        free(student);
        return NULL;
    }

    return student;
}

/**
 * @brief Frees all memory allocated for a student
 *
 * @param[in,out] student Pointer to the Student structure to be deallocated
 */
void student_destroy(Student *student)
{
    if (student == NULL)
    {
        return;
    }

    free(student->grades);
    free(student);
}

/**
 * @brief Adds a new grade to the student's grade record
 *
 * @param[in,out] student Pointer to the Student structure
 * @param[in]     grade   The grade value to be added
 *
 * @return True if the grade was added successfully, false otherwise
 */
bool student_add_grade(Student *student, double grade)
{
    if(!student || grade < 2.0 || grade > 5.0)
    {
        return false;
    }

    if(student->grades_count >= student->grades_capacity)
    {
        uint32_t new_capacity = student->grades_capacity * 2;
        double *new_grades = realloc(student->grades, sizeof(double) * new_capacity);

        if(!new_grades)
        {
            return false;
        }

        student->grades = new_grades;
        student->grades_capacity = new_capacity;
    }

    student->grades[student->grades_count] = grade;
    student->grades_count++;
    return true;
}

/**
 * @brief Calculates the average grade for a student
 *
 * @param[in,out] student Pointer to the Student structure
 *
 * @return True if the average was updated successfully, false if student is NULL or has no grades
 */
bool student_get_average_grade(Student *student)
{
    if(!student)
    {
        return false;
    }

    double total = 0.0;
    for(size_t i = 0; i < student->grades_count; i++)
    {
        total += student->grades[i];
    }

    student->grades_avg = total / (double)student->grades_count;
    return true;
}

/**
 * @brief Converts a Gender enum value to string
 *
 * @param[in] gender The Gender enum value to convert.
 *
 * @return Const pointer to a string literal
 */
const char* student_gender_to_string(Gender gender)
{
    switch(gender)
    {
        case MALE:
            return "Male";
        case FEMALE:
            return "Female";
        default:
            return "Unknown";
    }
}

/**
 * @brief Displays the details of student
 *
 * @param[in] student Pointer to the Student structure
 */
void display_student_details(const Student *student)
{
    if(!student)
    {
        printf("Student doesn't exist.\n");
    }

    printf("%d %s %s %s %s %s %lf\n",
         student->id,
         student->first_name,
         student->last_name,
         student->pesel,
         student->address,
         student_gender_to_string(student->gender),
         student->grades_avg);
}