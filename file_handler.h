#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "hash_table.h"

// Funções de manipulação de arquivos
bool load_concursos_from_file(HashTable* hash_table, const char* filename, char delimiter);

#endif
