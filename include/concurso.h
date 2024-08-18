#ifndef CONCURSO_H
#define CONCURSO_H

#include "hash_table.h"

// Function prototypes

/**
 * @brief Loads concursos from a CSV file and inserts them into the hash table.
 * 
 * @param hash_table Pointer to the hash table.
 * @param filename The name of the CSV file containing concursos.
 */
void load_concursos_from_file(HashTable* hash_table, const char* filename);

/**
 * @brief Counts the frequency of a specific number being drawn in the concursos.
 * 
 * @param hash_table Pointer to the hash table.
 * @param number The number to count frequency for.
 * @return int The frequency of the number.
 */
int count_number_frequency(HashTable* hash_table, int number);

/**
 * @brief Displays the top N most or least frequent numbers drawn.
 * 
 * @param hash_table Pointer to the hash table.
 * @param n The number of top numbers to display.
 * @param most_frequent If true, displays the most frequent; if false, displays the least frequent.
 */
void display_top_n_numbers(HashTable* hash_table, int n, int most_frequent);

/**
 * @brief Counts the number of concursos that occurred in a specific year.
 * 
 * @param hash_table Pointer to the hash table.
 * @param year The year to count concursos for.
 * @return int The number of concursos in that year.
 */
int count_concursos_in_year(HashTable* hash_table, int year);

#endif // CONCURSO_H