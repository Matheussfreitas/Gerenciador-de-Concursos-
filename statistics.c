#include "statistics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_NUMBERS 60

// Contar ocorrências de um número específico
void count_number_occurrences(HashTable* hash_table, int numero) {
    int count = 0;
    for (int i = 0; i < hash_table->size; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                if (current->numeros[j] == numero) {
                    count++;
                }
            }
            current = current->next;
        }
    }
    printf("O número %d apareceu %d vezes.\n", numero, count);
}

// Exibir os números mais ou menos sorteados
void display_top_numbers(HashTable* hash_table, int top_n, bool most_frequent) {
    int occurrences[TOTAL_NUMBERS] = {0};

    for (int i = 0; i < hash_table->size; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            for (int j = 0; j < 6; j++) {
                occurrences[current->numeros[j] - 1]++;
            }
            current = current->next;
        }
    }

    int indices[TOTAL_NUMBERS];
    for (int i = 0; i < TOTAL_NUMBERS; i++) {
        indices[i] = i + 1;
    }

    // Ordenar os números por frequência
    for (int i = 0; i < TOTAL_NUMBERS - 1; i++) {
        for (int j = i + 1; j < TOTAL_NUMBERS; j++) {
            if ((most_frequent && occurrences[i] < occurrences[j]) ||
                (!most_frequent && occurrences[i] > occurrences[j])) {
                int temp_occurrence = occurrences[i];
                occurrences[i] = occurrences[j];
                occurrences[j] = temp_occurrence;

                int temp_index = indices[i];
                indices[i] = indices[j];
                indices[j] = temp_index;
            }
        }
    }

    printf("Os %d números %s sorteados são:\n", top_n, most_frequent ? "mais" : "menos");
    for (int i = 0; i < top_n; i++) {
        printf("Número %d: %d vezes\n", indices[i], occurrences[i]);
    }
}

// Contar concursos em um determinado ano
void count_draws_in_year(HashTable* hash_table, int year) {
    int count = 0;

    for (int i = 0; i < hash_table->size; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            if (current->data_sorteio.tm_year + 1900 == year) {
                count++;
                printf("Concurso %d: Data %d-%02d-%02d, Números: ",
                       current->concurso_num,
                       current->data_sorteio.tm_year + 1900,
                       current->data_sorteio.tm_mon + 1,
                       current->data_sorteio.tm_mday);
                for (int j = 0; j < 6; j++) {
                    printf("%d ", current->numeros[j]);
                }
                printf("\n");
            }
            current = current->next;
        }
    }
    printf("Total de concursos realizados em %d: %d\n", year, count);
}
