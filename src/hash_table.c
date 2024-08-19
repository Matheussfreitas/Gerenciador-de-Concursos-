#include "../include/hash_table.h"
#include <stdio.h>  // Add this line to include printf and other standard I/O functions
#include <stdlib.h>
#include <string.h>

// Function to create a new node
Node* create_node(int concurso, const char* date, int numbers[6]) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL; // Handle memory allocation failure
    }
    new_node->concurso = concurso;
    strncpy(new_node->date, date, 11);
    memcpy(new_node->numbers, numbers, 6 * sizeof(int));
    new_node->next = NULL;
    return new_node;
}

// Hash function to map the concurso number to an index
unsigned int hash_function(int concurso) {
    return concurso % TABLE_SIZE;
}

// Function to initialize the hash table
HashTable* create_hash_table() {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    if (hash_table == NULL) {
        return NULL; // Handle memory allocation failure
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
}

// Function to insert a new concurso into the hash table
// Function to insert a new concurso into the hash table
void insert_concurso(HashTable* hash_table, int concurso, const char* date, int numbers[6]) {
    unsigned int index = hash_function(concurso);

    // Verifica se o concurso já existe na tabela
    Node* current = hash_table->table[index];
    while (current != NULL) {
        if (current->concurso == concurso) {
            printf("Concurso %d já existe e não pode ser duplicado.\n", concurso);
            return; // Não insere um concurso duplicado e retorna imediatamente
        }
        current = current->next;
    }

    // Se não existir, cria um novo nó e insere na lista
    Node* new_node = create_node(concurso, date, numbers);
    if (new_node == NULL) {
        printf("Falha na alocação de memória para o novo concurso.\n");
        return;
    }

    if (hash_table->table[index] == NULL) {
        hash_table->table[index] = new_node;
    } else {
        // Colisão tratada com encadeamento (lista ligada)
        current = hash_table->table[index]; // Reinicia o ponteiro 'current' para a cabeça da lista
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    printf("Concurso %d inserido com sucesso.\n", concurso);
}
// Function to search for a concurso in the hash table
Node* search_concurso(HashTable* hash_table, int concurso) {
    unsigned int index = hash_function(concurso);
    Node* current = hash_table->table[index];

    while (current != NULL) {
        if (current->concurso == concurso) {
            return current;
        }
        current = current->next;
    }

    return NULL; // Not found
}

// Function to remove a concurso from the hash table
void remove_concurso(HashTable* hash_table, int concurso) {
    unsigned int index = hash_function(concurso);
    Node* current = hash_table->table[index];
    Node* previous = NULL;

    while (current != NULL && current->concurso != concurso) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Concurso %d not found.\n", concurso); // printf requires stdio.h
        return; // Not found
    }

    if (previous == NULL) {
        // Remove the first node in the chain
        hash_table->table[index] = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Concurso %d removed.\n", concurso); // printf requires stdio.h
}

// Function to display all concursos in the hash table
void display_concursos(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            printf("Concurso: %d, Date: %s, Numbers: ", current->concurso, current->date); // printf requires stdio.h
            for (int j = 0; j < 6; j++) {
                printf("%d ", current->numbers[j]);
            }
            printf("\n");
            current = current->next;
        }
    }
}

// Function to free the memory allocated for the hash table
void free_hash_table(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hash_table);
}