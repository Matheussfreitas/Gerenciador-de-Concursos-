#include "hash_table.h"
#include "utils.h"
#include "concurso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_concursos_from_file(HashTable *hash_table, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    char line[256];
    char delimiter;

    // Determina o delimitador com base na extensão do arquivo
    if (strstr(filename, ".csv") != NULL)
    {
        delimiter = ',';
    }
    else if (strstr(filename, ".tsv") != NULL)
    {
        delimiter = '\t';
    }
    else
    {
        printf("Formato de arquivo não suportado. Use .csv ou .tsv.\n");
        fclose(file);
        return;
    }

    // Lê cada linha do arquivo
    while (fgets(line, sizeof(line), file))
    {
        int concurso;
        char date[11];
        int numbers[6];

        // Usa strtok para separar os valores da linha
        char *token = strtok(line, &delimiter);
        if (token != NULL)
            concurso = atoi(token);

        token = strtok(NULL, &delimiter);
        if (token != NULL)
            strncpy(date, token, 10);

        for (int i = 0; i < 6; i++)
        {
            token = strtok(NULL, &delimiter);
            if (token != NULL)
                numbers[i] = atoi(token);
        }

        if (concurso != 0 && strlen(date) > 0)
        {
            // Insere os dados na tabela de dispersão
            insert_concurso(hash_table, concurso, date, numbers);
        }
    }

    printf("Concursos carregados de %s.\n", filename);
    fclose(file);
}
// Function to count how many times a specific number was drawn
int count_number_frequency(HashTable *hash_table, int number)
{
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = hash_table->table[i];
        while (current != NULL)
        {
            for (int j = 0; j < 6; j++)
            {
                if (current->numbers[j] == number)
                {
                    count++;
                }
            }
            current = current->next;
        }
    }

    return count;
}

// Function to display the top N most frequent numbers
void display_top_n_numbers(HashTable *hash_table, int n, int most_frequent)
{
    int frequency[60] = {0};

    // Count frequency of each number
    for (int i = 1; i <= 60; i++)
    {
        frequency[i - 1] = count_number_frequency(hash_table, i);
    }

    // Sort and display the top N numbers
    for (int i = 0; i < n; i++)
    {
        int max_index = 0;
        for (int j = 1; j < 60; j++)
        {
            if ((most_frequent && frequency[j] > frequency[max_index]) ||
                (!most_frequent && frequency[j] < frequency[max_index]))
            {
                max_index = j;
            }
        }

        printf("%d: %d times\n", max_index + 1, frequency[max_index]);
        frequency[max_index] = most_frequent ? -1 : 999999; // Mark as processed
    }
}

// Function to count the number of concursos in a specific year
int count_concursos_in_year(HashTable *hash_table, int year)
{
    int count = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = hash_table->table[i];
        while (current != NULL)
        {
            int concurso_year;
            sscanf(current->date + 6, "%d", &concurso_year); // Extract year from date
            if (concurso_year == year)
            {
                count++;
            }
            current = current->next;
        }
    }

    return count;
}