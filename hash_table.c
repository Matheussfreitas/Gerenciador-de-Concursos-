#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_MULTIPLIER 31

// Função hash
unsigned int hash_function(int concurso_num, int table_size) {
    return (unsigned int)(concurso_num % table_size);
}

// Criar tabela de dispersão
HashTable* create_table(int size) {
    HashTable* new_table = (HashTable*)malloc(sizeof(HashTable));
    if (new_table == NULL) {
        perror("Erro ao alocar memória para a tabela de dispersão");
        return NULL;
    }

    new_table->table = (Node**)malloc(size * sizeof(Node*));
    if (new_table->table == NULL) {
        perror("Erro ao alocar memória para as entradas da tabela");
        free(new_table);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        new_table->table[i] = NULL;
    }
    new_table->size = size;
    return new_table;
}

// Inserir concurso
bool insert_concurso(HashTable* hash_table, int concurso_num, struct tm data_sorteio, int numeros[6]) {
    unsigned int index = hash_function(concurso_num, hash_table->size);
    Node* current = hash_table->table[index];

    // Verificar duplicação
    while (current != NULL) {
        if (current->concurso_num == concurso_num) {
            printf("Concurso %d já existe na tabela.\n", concurso_num);
            return false;
        }
        current = current->next;
    }

    // Inserir novo concurso
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Erro ao alocar memória para o novo concurso");
        return false;
    }

    new_node->concurso_num = concurso_num;
    new_node->data_sorteio = data_sorteio;
    memcpy(new_node->numeros, numeros, 6 * sizeof(int));
    new_node->next = hash_table->table[index];
    hash_table->table[index] = new_node;

    return true;
}

// Buscar concurso
Node* search_concurso(HashTable* hash_table, int concurso_num) {
    unsigned int index = hash_function(concurso_num, hash_table->size);
    Node* current = hash_table->table[index];

    while (current != NULL) {
        if (current->concurso_num == concurso_num) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Remover concurso
bool remove_concurso(HashTable* hash_table, int concurso_num) {
    unsigned int index = hash_function(concurso_num, hash_table->size);
    Node* current = hash_table->table[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (current->concurso_num == concurso_num) {
            if (prev == NULL) {
                hash_table->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Visualizar todos os concursos
void display_all_concursos(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            printf("Concurso %d: Data %d-%02d-%02d, Números: ", current->concurso_num,
                   current->data_sorteio.tm_year + 1900,
                   current->data_sorteio.tm_mon + 1,
                   current->data_sorteio.tm_mday);
            for (int j = 0; j < 6; j++) {
                printf("%d ", current->numeros[j]);
            }
            printf("\n");
            current = current->next;
        }
    }
}

// Liberar memória da tabela
void free_table(HashTable* hash_table) {
    for (int i = 0; i < hash_table->size; i++) {
        Node* current = hash_table->table[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hash_table->table);
    free(hash_table);
}
