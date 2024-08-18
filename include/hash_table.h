#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 100  // Define the size of the hash table

// Node structure for linked list in hash table
typedef struct Node {
    int concurso;
    char date[11];  // Format: DD-MM-YYYY
    int numbers[6];
    struct Node* next;
} Node;

// Hash table structure
typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

// Function prototypes
Node* create_node(int concurso, const char* date, int numbers[6]);
HashTable* create_hash_table();
void insert_concurso(HashTable* hash_table, int concurso, const char* date, int numbers[6]);
Node* search_concurso(HashTable* hash_table, int concurso);
void remove_concurso(HashTable* hash_table, int concurso);
void display_concursos(HashTable* hash_table);
void free_hash_table(HashTable* hash_table);

#endif // HASH_TABLE_H