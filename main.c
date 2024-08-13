#define _XOPEN_SOURCE 700
#include "hash_table.h"
#include "statistics.h"
#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 100

void print_menu() {
    printf("Gerenciador de Concursos da Mega-Sena\n");
    printf("1. Inserir Concurso\n");
    printf("2. Buscar Concurso\n");
    printf("3. Remover Concurso\n");
    printf("4. Visualizar Todos os Concursos\n");
    printf("5. Carregar Concursos de um Arquivo\n");
    printf("6. Apresentar Estatísticas\n");
    printf("7. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    HashTable* hash_table = create_table(TABLE_SIZE);

    int option;
    do {
        print_menu();
        scanf("%d", &option);

        if (option == 1) {
            int concurso_num;
            int numeros[6];
            struct tm data_sorteio;
            char data_str[11];

            printf("Digite o número do concurso: ");
            scanf("%d", &concurso_num);

            printf("Digite a data do sorteio (dd-mm-aaaa): ");
            scanf("%s", data_str);
            strptime(data_str, "%d-%m-%Y", &data_sorteio);

            printf("Digite os seis números sorteados: ");
            for (int i = 0; i < 6; i++) {
                scanf("%d", &numeros[i]);
            }

            if (insert_concurso(hash_table, concurso_num, data_sorteio, numeros)) {
                printf("Concurso inserido com sucesso!\n");
            }

        } else if (option == 2) {
            int concurso_num;
            printf("Digite o número do concurso: ");
            scanf("%d", &concurso_num);

            Node* result = search_concurso(hash_table, concurso_num);
            if (result) {
                printf("Concurso %d: Data %d-%02d-%02d, Números: ",
                       result->concurso_num,
                       result->data_sorteio.tm_year + 1900,
                       result->data_sorteio.tm_mon + 1,
                       result->data_sorteio.tm_mday);
                for (int i = 0; i < 6; i++) {
                    printf("%d ", result->numeros[i]);
                }
                printf("\n");
            } else {
                printf("Concurso não encontrado.\n");
            }

        } else if (option == 3) {
            int concurso_num;
            printf("Digite o número do concurso: ");
            scanf("%d", &concurso_num);

            if (remove_concurso(hash_table, concurso_num)) {
                printf("Concurso removido com sucesso!\n");
            } else {
                printf("Concurso não encontrado.\n");
            }

        } else if (option == 4) {
            display_all_concursos(hash_table);

        } else if (option == 5) {
            char filename[100];
            char delimiter;
            printf("Digite o nome do arquivo (CSV ou TSV): ");
            scanf("%s", filename);
            printf("Digite o delimitador (, para CSV ou \\t para TSV): ");
            scanf(" %c", &delimiter);

            if (load_concursos_from_file(hash_table, filename, delimiter)) {
                printf("Concursos carregados com sucesso!\n");
            } else {
                printf("Erro ao carregar concursos.\n");
            }

        } else if (option == 6) {
            int stat_option;
            printf("1. Quantidade de sorteios de um número\n");
            printf("2. Dez números mais sorteados\n");
            printf("3. Dez números menos sorteados\n");
            printf("4. Quantidade de concursos em um determinado ano\n");
            printf("Escolha uma opção: ");
            scanf("%d", &stat_option);

            if (stat_option == 1) {
                int numero;
                printf("Digite o número: ");
                scanf("%d", &numero);
                count_number_occurrences(hash_table, numero);

            } else if (stat_option == 2) {
                display_top_numbers(hash_table, 10, true);

            } else if (stat_option == 3) {
                display_top_numbers(hash_table, 10, false);

            } else if (stat_option == 4) {
                int year;
                printf("Digite o ano: ");
                scanf("%d", &year);
                count_draws_in_year(hash_table, year);
            }
        }
    } while (option != 7);

    free_table(hash_table);
    return 0;
}
