#ifndef STATISTICS_H
#define STATISTICS_H

#include "hash_table.h"

// Funções de estatísticas
void count_number_occurrences(HashTable* hash_table, int numero);
void display_top_numbers(HashTable* hash_table, int top_n, bool most_frequent);
void count_draws_in_year(HashTable* hash_table, int year);

#endif
