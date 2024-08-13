#define _XOPEN_SOURCE 700
#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para carregar concursos de um arquivo CSV ou TSV
bool load_concursos_from_file(HashTable* hash_table, const char* filename, char delimiter) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return false;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        int concurso_num;
        struct tm data_sorteio;
        int numeros[6];

        // Parse da linha do arquivo
        char* token = strtok(line, &delimiter);
        concurso_num = atoi(token);

        token = strtok(NULL, &delimiter);
        strptime(token, "%d-%m-%Y", &data_sorteio);

        for (int i = 0; i < 6; i++) {
            token = strtok(NULL, &delimiter);
            numeros[i] = atoi(token);
        }

        insert_concurso(hash_table, concurso_num, data_sorteio, numeros);
    }

    fclose(file);
    return true;
}
