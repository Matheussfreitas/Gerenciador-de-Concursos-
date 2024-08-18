#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Trims leading and trailing whitespace from a string.
 * 
 * @param str The string to be trimmed.
 * @return char* The trimmed string.
 */
char* trim_whitespace(char* str);

/**
 * @brief Splits a string by a specified delimiter.
 * 
 * @param str The string to be split.
 * @param delimiter The character delimiter to split the string.
 * @param count Pointer to an integer where the number of split parts will be stored.
 * @return char** An array of strings resulting from the split. The caller is responsible for freeing the memory.
 */
char** split_string(const char* str, const char delimiter, int* count);

/**
 * @brief Frees the memory allocated by split_string function.
 * 
 * @param result The array of strings to be freed.
 */
void free_split_result(char** result);

/**
 * @brief Converts a date string in the format "DD-MM-YYYY" to an integer in the format YYYYMMDD.
 * 
 * @param date The date string to be converted.
 * @return int The converted date as an integer.
 */
int convert_date_to_int(const char* date);

/**
 * @brief Checks if a string is a valid integer.
 * 
 * @param str The string to check.
 * @return int 1 if the string is a valid integer, 0 otherwise.
 */
int is_valid_integer(const char* str);

#endif // UTILS_H