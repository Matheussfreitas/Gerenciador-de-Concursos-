#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <time.h>

// Estrutura para armazenar dados de cada concurso
typedef struct Node {
    int concurso_num;
    struct tm data_sorteio;
    int numeros[6];
    struct Node* next; // Para o tratamento de colisões (chaining)
} Node;

// Tabela de dispersão
typedef struct {
    Node** table;
    int size;
} HashTable;

// Funções da tabela de dispersão
HashTable* create_table(int size);
bool insert_concurso(HashTable* hash_table, int concurso_num, struct tm data_sorteio, int numeros[6]);
Node* search_concurso(HashTable* hash_table, int concurso_num);
bool remove_concurso(HashTable* hash_table, int concurso_num);
void display_all_concursos(HashTable* hash_table);
void free_table(HashTable* hash_table);

#endif
