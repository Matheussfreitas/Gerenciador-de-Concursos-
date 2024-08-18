#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "concurso.h"
#include "utils.h"

// Function prototypes
void display_menu();
void handle_insert_concurso(HashTable* hash_table);
void handle_search_concurso(HashTable* hash_table);
void handle_remove_concurso(HashTable* hash_table);
void handle_display_all_concursos(HashTable* hash_table);
void handle_load_from_file(HashTable* hash_table);
void handle_display_statistics(HashTable* hash_table);

int main() {
    HashTable* hash_table = create_hash_table();
    int choice;

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1:
                handle_insert_concurso(hash_table);
                break;
            case 2:
                handle_search_concurso(hash_table);
                break;
            case 3:
                handle_remove_concurso(hash_table);
                break;
            case 4:
                handle_display_all_concursos(hash_table);
                break;
            case 5:
                handle_load_from_file(hash_table);
                break;
            case 6:
                handle_display_statistics(hash_table);
                break;
            case 0:
                printf("Exiting...\n");
                free_hash_table(hash_table);
                exit(0);
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    }

    return 0;
}

void display_menu() {
    printf("\nMega-Sena Manager\n");
    printf("1. Insert Concurso\n");
    printf("2. Search Concurso\n");
    printf("3. Remove Concurso\n");
    printf("4. Display All Concursos\n");
    printf("5. Load Concursos from File\n");
    printf("6. Display Statistics\n");
    printf("0. Exit\n");
}

void handle_insert_concurso(HashTable* hash_table) {
    int concurso, numbers[6];
    char date[11];

    printf("Enter concurso number: ");
    scanf("%d", &concurso);
    printf("Enter date (DD-MM-YYYY): ");
    scanf("%s", date);
    printf("Enter 6 numbers (space-separated): ");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &numbers[i]);
    }

    insert_concurso(hash_table, concurso, date, numbers);
    printf("Concurso %d inserted successfully.\n", concurso);
}

void handle_search_concurso(HashTable* hash_table) {
    int concurso;
    printf("Enter concurso number to search: ");
    scanf("%d", &concurso);

    Node* result = search_concurso(hash_table, concurso);
    if (result) {
        printf("Concurso: %d, Date: %s, Numbers: ", result->concurso, result->date);
        for (int i = 0; i < 6; i++) {
            printf("%d ", result->numbers[i]);
        }
        printf("\n");
    } else {
        printf("Concurso %d not found.\n", concurso);
    }
}

void handle_remove_concurso(HashTable* hash_table) {
    int concurso;
    printf("Enter concurso number to remove: ");
    scanf("%d", &concurso);

    remove_concurso(hash_table, concurso);
}

void handle_display_all_concursos(HashTable* hash_table) {
    printf("Displaying all concursos:\n");
    display_concursos(hash_table);
}

void handle_load_from_file(HashTable* hash_table) {
    char filename[256];
    printf("Enter filename to load concursos from: ");
    scanf("%s", filename);

    load_concursos_from_file(hash_table, filename);
    printf("Concursos loaded from %s.\n", filename);
}

void handle_display_statistics(HashTable* hash_table) {
    int choice, n, year, number;

    printf("Statistics Menu:\n");
    printf("1. Count frequency of a specific number\n");
    printf("2. Display top N most frequent numbers\n");
    printf("3. Display top N least frequent numbers\n");
    printf("4. Count concursos in a specific year\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter the number to count frequency: ");
            scanf("%d", &number);
            printf("Number %d was drawn %d times.\n", number, count_number_frequency(hash_table, number));
            break;
        case 2:
            printf("Enter N for top N most frequent numbers: ");
            scanf("%d", &n);
            display_top_n_numbers(hash_table, n, 1);
            break;
        case 3:
            printf("Enter N for top N least frequent numbers: ");
            scanf("%d", &n);
            display_top_n_numbers(hash_table, n, 0);
            break;
        case 4:
            printf("Enter the year to count concursos: ");
            scanf("%d", &year);
            printf("There were %d concursos in %d.\n", count_concursos_in_year(hash_table, year), year);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}