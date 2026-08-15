#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
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

/**
 * @brief Remove a student from the database record
 *
 * @param[in,out] database Pointer to the Database structure
 * @param[in]     id       The student ID
 *
 * @return True if the student was removed successfully, false otherwise
 */
bool remove_student_by_id(Database *database, uint32_t id)
{
    if(!database || !database->students || database->size == 0)
    {
        return false;
    }

    size_t index = database->size;
    for (size_t i = 0; i < database->size; i++)
    {
        if(database->students[i].id == id)
        {
            index = i;
            break;
        }
    }

    if(index == database->size)
    {
        return false;
    }

    student_destroy(&database->students[index]);

    for (size_t i = index; i < database->size - 1; i++)
    {
        database->students[i] = database->students[i + 1];
    }

    database->size--;
    memset(&database->students[database->size], 0, sizeof(Student));

    return true;
}

/**
 * @brief Remove a student from the database record
 *
 * @param[in,out] database Pointer to the Database structure
 * @param[in]     pesel    The student PESEL
 *
 * @return True if the student was removed successfully, false otherwise
 */
bool remove_student_by_pesel(Database *database, const char *pesel)
{
    if(!database || !database->students || database->size == 0 || !pesel)
    {
        return false;
    }

    size_t index = database->size;
    for (size_t i = 0; i < database->size; i++)
    {
        if(strcmp(database->students[i].pesel, pesel) == 0)
        {
            index = i;
            break;
        }
    }

    if(index == database->size)
    {
        return false;
    }

    student_destroy(&database->students[index]);

    for (size_t i = index; i < database->size - 1; i++)
    {
        database->students[i] = database->students[i + 1];
    }

    database->size--;
    memset(&database->students[database->size], 0, sizeof(Student));

    return true;
}

/**
 * @brief Find a student from the database record
 *
 * @param[in] database Pointer to the Database structure
 * @param[in] id       The student ID
 *
 * @return Pointer to the allocated Student object within the database if found, or NULL if not found
 */
Student* find_student_by_id(const Database *database, uint32_t id)
{
    if(!database || !database->students || database->size == 0)
    {
        return NULL;
    }

    for (size_t i = 0; i < database->size; i++)
    {
        if(database->students[i].id == id)
        {
            return &database->students[i];
        }
    }

    return NULL;
}

/**
 * @brief Find a student from the database record
 *
 * @param[in] database Pointer to the Database structure
 * @param[in] pesel    The student PESEL
 *
 * @return Pointer to the allocated Student object within the database if found, or NULL if not found
 */
Student* find_student_by_pesel(const Database *database, const char *pesel)
{
    if(!database || !database->students || database->size == 0 || !pesel)
    {
        return NULL;
    }

    for (size_t i = 0; i < database->size; i++)
    {
        if(strcmp(database->students[i].pesel, pesel) == 0)
        {
            return &database->students[i];
        }
    }

    return NULL;
}

/**
 * @brief Display all students details from the database
 *
 * @param[in] database Pointer to the Database structure
 */
void display_all_students(const Database *database)
{
    if(!database || !database->students || database->size == 0)
    {
        perror("Students does not exist!");
    }

    printf("\n%-6s | %-20s | %-30s | %-7s\n", "ID", "First Name", "Last Name", "Average Grade");
    printf("------------------------------------------------------------------------------\n");

    for(size_t i = 0; i < database->size; i++)
    {
        printf("%-6d | %-20s | %-30s | %-7.2f\n",
            database->students[i].id,
            database->students[i].first_name,
            database->students[i].last_name,
            database->students[i].grades_avg
        );
    }
}

/**
 * @brief Display the current number of students in the database
 *
 * @param[in] database Pointer to the Database structure
 *
 * @return The number of students currently stored in the database
 */
size_t display_database_size(const Database *database)
{
    if(!database || !database->students || database->size == 0)
    {
        return INITIAL_DATABASE_SIZE;
    }

    return database->size;
}

/**
 * @brief Saves database records to binary file
 *
 * @param[in] database Pointer to the Database structure to be saved
 * @param[in] path     Destination file path
 */
void save_database_to_file(const Database *database, const char *path)
{
    if (!database || !path || !database->students)
    {
        return;
    }

    FILE *file = fopen(path, "wb");
    if(file == NULL)
    {
        perror("Error opening file for writing");
        return;
    }

    if(fwrite(&database->size, sizeof(database->size), 1, file) != 1)
    {
        perror("Error writing database size");
        fclose(file);
        return;
    }

    if(database->size > 0)
    {
        size_t written_items = fwrite(database->students, sizeof(Student), database->size, file);
        if (written_items != database->size) {
            perror("Error writing student records");
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Successfully saved the database\n");
}

/**
 * @brief Opens a binary file and loads database records into memory
 *
 * @param[in,out] database Pointer to the Database structure to be saved
 * @param[in]     path     Destination file path
 */
void open_database_from_file(Database *database, const char *path)
{
    if (!database || !path) {
        fprintf(stderr, "Error: Invalid argument passed to open_database_from_file");
        return;
    }

    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    size_t new_size = 0;
    if (fread(&new_size, sizeof(new_size), 1, file) != 1) {
        perror("Error reading database size from file");
        fclose(file);
        return;
    }

    if (new_size > 0) {
        Student *new_students = realloc(database->students, new_size * sizeof(Student));
        if (new_students == NULL) {
            perror("Error reallocating memory for loaded students");
            fclose(file);
            return;
        }

        database->students = new_students;

        if (fread(database->students, sizeof(Student), new_size, file) != new_size) {
            perror("Error reading student records from file");
            fclose(file);
            return;
        }
    }

    database->size = new_size;
    database->capacity = new_size;

    fclose(file);
    printf("Successfully loaded %zu records from %s\n", new_size, path);
}

/**
 * @brief Saves database records to a JSON file
 *
 * @param[in] database Pointer to the Database structure to save
 * @param[in] path     Destination JSON file path
 */
void save_database_to_json(const Database *database, const char *path)
{
    if(!database || !path)
    {
        fprintf(stderr, "Invalid argument passed to save_database_to_json\n");
        return;
    }

    cJSON *root = cJSON_CreateObject();
    if (root == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for JSON object\n");
        return;
    }

    cJSON *students_array = cJSON_CreateArray();
    if (students_array == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for JSON array\n");
        cJSON_Delete(root);
        return;
    }
    cJSON_AddItemToObject(root, "students", students_array);


    if (database->students != NULL)
    {
        for (size_t i = 0; i < database->size; i++)
        {
            cJSON *student_obj = cJSON_CreateObject();
            if (student_obj == NULL)
            {
                continue;
            }

            cJSON_AddNumberToObject(student_obj, "id", database->students[i].id);
            cJSON_AddStringToObject(student_obj, "first_name", database->students[i].first_name);
            cJSON_AddStringToObject(student_obj, "last_name", database->students[i].last_name);
            cJSON_AddStringToObject(student_obj, "pesel", database->students[i].pesel);
            cJSON_AddStringToObject(student_obj, "address", database->students[i].address);
            cJSON_AddStringToObject(student_obj, "gender", student_gender_to_string(database->students[i].gender));

            if (database->students[i].grades != NULL && database->students[i].grades_count > 0)
            {
                cJSON *grades_array = cJSON_CreateDoubleArray(
                    database->students[i].grades,
                    (int)database->students[i].grades_count
                );
                cJSON_AddItemToObject(student_obj, "grades", grades_array);
            } else
            {
                cJSON_AddItemToObject(student_obj, "grades", cJSON_CreateArray());
            }
            cJSON_AddNumberToObject(student_obj, "grades_avg", database->students[i].grades_avg);
            cJSON_AddItemToArray(students_array, student_obj);
        }
    }

    char *json_string = cJSON_Print(root);
    if (json_string == NULL)
    {
        fprintf(stderr, "Failed to render JSON string.\n");
        cJSON_Delete(root);
        return;
    }

    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        perror("Error opening file for JSON write");
        cJSON_free(json_string);
        cJSON_Delete(root);
        return;
    }

    fputs(json_string, file);

    fclose(file);
    cJSON_free(json_string);
    cJSON_Delete(root);

    printf("Successfully saved %zu records to %s (JSON)\n", database->size, path);
}

/**
 * @brief Helper for open_database_from_json function
 */
static void parse_student(const cJSON *item, Student *student)
{
    memset(student, 0, sizeof(*student));

    cJSON *id = cJSON_GetObjectItemCaseSensitive(item, "id");
    cJSON *first_name = cJSON_GetObjectItemCaseSensitive(item, "first_name");
    cJSON *last_name = cJSON_GetObjectItemCaseSensitive(item, "last_name");
    cJSON *pesel = cJSON_GetObjectItemCaseSensitive(item, "pesel");
    cJSON *address = cJSON_GetObjectItemCaseSensitive(item, "address");
    cJSON *gender = cJSON_GetObjectItemCaseSensitive(item, "gender");
    cJSON *grades = cJSON_GetObjectItemCaseSensitive(item, "grades");
    cJSON *grades_avg = cJSON_GetObjectItemCaseSensitive(item, "grades_avg");

    if (cJSON_IsNumber(id))
    {
        student->id = (uint32_t)id->valueint;
    }

    if (cJSON_IsString(first_name) && first_name->valuestring)
    {
        strncpy(student->first_name, first_name->valuestring, sizeof(student->first_name) - 1);
    }

    if (cJSON_IsString(last_name) && last_name->valuestring)
    {
        strncpy(student->last_name, last_name->valuestring, sizeof(student->last_name) - 1);
    }

    if (cJSON_IsString(pesel) && pesel->valuestring)
    {
        strncpy(student->pesel, pesel->valuestring, sizeof(student->pesel) - 1);
    }

    if (cJSON_IsString(address) && address->valuestring)
    {
        strncpy(student->address, address->valuestring, sizeof(student->address) - 1);
    }

    if (cJSON_IsString(gender) && gender->valuestring)
    {
        student->gender = student_gender_from_string(gender->valuestring);
    }

    if (cJSON_IsNumber(grades_avg))
    {
        student->grades_avg = grades_avg->valuedouble;
    }

    if (cJSON_IsArray(grades)) {
        int32_t count = cJSON_GetArraySize(grades);
        if (count > 0 && (student->grades = malloc((size_t)count * sizeof(double))))
        {
            student->grades_count = (size_t)count;
            uint32_t index = 0;
            cJSON *g = NULL;
            cJSON_ArrayForEach(g, grades)
            {
                if (cJSON_IsNumber(g)) student->grades[index++] = g->valuedouble;
            }
        }
    }
}

/**
 * @brief Opens a json file and loads database records into memory
 *
 * @param[in,out] database Pointer to the Database structure to be saved
 * @param[in]     path     Destination file path
 */
void open_database_from_json(Database *database, const char *path)
{
    if(!database || !path)
    {
        return;
    }

    FILE *file = fopen(path, "rb");
    if(!file)
    {
        perror("Error opening JSON file");
        return;
    }

    fseek(file, 0, SEEK_END);
    int64_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if(length <= 0)
    {
        fclose(file); return;
    }

    char *buffer = malloc((size_t)length + 1);
    if(!buffer)
    {
        fclose(file);
        return;
    }

    size_t read_bytes = fread(buffer, 1, (size_t)length, file);
    fclose(file);
    buffer[read_bytes] = '\0';

    cJSON *root = cJSON_Parse(buffer);
    free(buffer);
    if (!root)
    {
        return;
    }

    cJSON *students_array = cJSON_GetObjectItemCaseSensitive(root, "students");
    if (cJSON_IsArray(students_array))
    {
        cJSON *student_json = NULL;
        cJSON_ArrayForEach(student_json, students_array)
        {
            if (cJSON_IsObject(student_json))
            {
                Student student;
                parse_student(student_json, &student);
                add_student(database, &student);
                free(student.grades);
            }
        }
    }

    cJSON_Delete(root);
    printf("Successfully loaded records from %s (JSON)\n", path);
}