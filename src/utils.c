#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Function to trim leading and trailing whitespace from a string
char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (*str == ' ') str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}

// Function to split a string by a delimiter
char** split_string(const char* str, const char delimiter, int* count) {
    char* token;
    char* str_copy = strdup(str);
    char** result = NULL;
    int spaces = 0;

    token = strtok(str_copy, &delimiter);
    while (token) {
        result = realloc(result, sizeof(char*) * ++spaces);
        if (result == NULL) {
            free(str_copy);
            return NULL; // Memory allocation failed
        }
        result[spaces - 1] = strdup(token);
        token = strtok(NULL, &delimiter);
    }

    // Add NULL terminator at the end
    result = realloc(result, sizeof(char*) * (spaces + 1));
    result[spaces] = NULL;

    *count = spaces;

    free(str_copy);
    return result;
}

// Function to free the memory allocated for the result of split_string
void free_split_result(char** result) {
    if (result) {
        int i = 0;
        while (result[i]) {
            free(result[i]);
            i++;
        }
        free(result);
    }
}

// Function to convert a string date "DD-MM-YYYY" to an integer in the format YYYYMMDD
int convert_date_to_int(const char* date) {
    int day, month, year;
    sscanf(date, "%2d-%2d-%4d", &day, &month, &year);
    return year * 10000 + month * 100 + day;
}

// Function to check if a string is a valid integer
int is_valid_integer(const char* str) {
    if (*str == '-' || *str == '+') str++; // Skip the sign if present
    while (*str) {
        if (*str < '0' || *str > '9') return 0; // Not a valid integer
        str++;
    }
    return 1;
}