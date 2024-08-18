#include "hash_table.h"
#include "utils.h"
#include "concurso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_concursos_from_file(HashTable* hash_table, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[256];
    char delimiter = ',';  // Default delimiter for CSV

    // Detect if file is TSV based on the file extension
    const char *ext = strrchr(filename, '.');
    if (ext && strcmp(ext, ".tsv") == 0) {
        delimiter = '\t';
    }

    while (fgets(line, sizeof(line), file)) {
        char* trimmed_line = trim_whitespace(line);

        // Ignore empty lines
        if (strlen(trimmed_line) == 0) {
            continue;
        }

        int count;
        char** tokens = split_string(trimmed_line, delimiter, &count);

        // Check if we have exactly 8 fields (concurso, date, 6 numbers)
        if (count != 8) {
            printf("Warning: Incorrect format in line: %s\n", trimmed_line);
            free_split_result(tokens);
            continue;
        }

        int concurso = atoi(tokens[0]);
        char* date = tokens[1];
        int numbers[6];

        int valid_numbers = 1;
        for (int i = 0; i < 6; i++) {
            if (!is_valid_integer(tokens[i + 2])) {
                valid_numbers = 0;
                break;
            }
            numbers[i] = atoi(tokens[i + 2]);

            // Check if the number is within the valid range (1 to 60)
            if (numbers[i] < 1 || numbers[i] > 60) {
                valid_numbers = 0;
                break;
            }
        }

        if (!valid_numbers) {
            printf("Warning: Invalid numbers in line: %s\n", trimmed_line);
            free_split_result(tokens);
            continue;
        }

        insert_concurso(hash_table, concurso, date, numbers);
        free_split_result(tokens);
    }

    fclose(file);
    printf("File %s loaded successfully.\n", filename);
}

// Function to count how many times a specific number was drawn
int count_number_frequency(HashTable* hash_table, int number) {
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                if (current->numbers[j] == number) {
                    count++;
                }
            }
            current = current->next;
        }
    }

    return count;
}

// Function to display the top N most frequent numbers
void display_top_n_numbers(HashTable* hash_table, int n, int most_frequent) {
    int frequency[60] = {0};

    // Count frequency of each number
    for (int i = 1; i <= 60; i++) {
        frequency[i - 1] = count_number_frequency(hash_table, i);
    }

    // Sort and display the top N numbers
    for (int i = 0; i < n; i++) {
        int max_index = 0;
        for (int j = 1; j < 60; j++) {
            if ((most_frequent && frequency[j] > frequency[max_index]) ||
                (!most_frequent && frequency[j] < frequency[max_index])) {
                max_index = j;
            }
        }

        printf("%d: %d times\n", max_index + 1, frequency[max_index]);
        frequency[max_index] = most_frequent ? -1 : 999999; // Mark as processed
    }
}

// Function to count the number of concursos in a specific year
int count_concursos_in_year(HashTable* hash_table, int year) {
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            int concurso_year;
            sscanf(current->date + 6, "%d", &concurso_year); // Extract year from date
            if (concurso_year == year) {
                count++;
            }
            current = current->next;
        }
    }

    return count;
}