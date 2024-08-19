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
        printf("Digite sua escolha: ");
        if (scanf("%d", &choice) != 1) {
            printf("Entrada inválida. Por favor, insira um número.\n");
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
                printf("Saindo...\n");
                free_hash_table(hash_table);
                exit(0);
            default:
                printf("Escolha inválida. Por favor, selecione uma opção válida.\n");
                break;
        }
    }

    return 0;
}

void display_menu() {
    printf("\nGerenciador da Mega-Sena\n");
    printf("1. Inserir Concurso\n");
    printf("2. Buscar Concurso\n");
    printf("3. Remover Concurso\n");
    printf("4. Exibir Todos os Concursos\n");
    printf("5. Carregar Concursos de um Arquivo\n");
    printf("6. Exibir Estatísticas\n");
    printf("0. Sair\n");
}

void handle_insert_concurso(HashTable* hash_table) {
    int concurso, numbers[6];
    char date[11];

    printf("Digite o número do concurso: ");
    scanf("%d", &concurso);
    printf("Digite a data (DD-MM-AAAA): ");
    scanf("%s", date);
    printf("Digite os 6 números (separados por espaço): ");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &numbers[i]);
    }

    insert_concurso(hash_table, concurso, date, numbers);
}

void handle_search_concurso(HashTable* hash_table) {
    int concurso;
    printf("Digite o número do concurso para buscar: ");
    scanf("%d", &concurso);

    Node* result = search_concurso(hash_table, concurso);
    if (result) {
        printf("Concurso: %d, Data: %s, Números: ", result->concurso, result->date);
        for (int i = 0; i < 6; i++) {
            printf("%d ", result->numbers[i]);
        }
        printf("\n");
    } else {
        printf("Concurso %d não encontrado.\n", concurso);
    }
}

void handle_remove_concurso(HashTable* hash_table) {
    int concurso;
    printf("Digite o número do concurso para remover: ");
    scanf("%d", &concurso);

    remove_concurso(hash_table, concurso);
}

void handle_display_all_concursos(HashTable* hash_table) {
    printf("Exibindo todos os concursos:\n");
    display_concursos(hash_table);
}

void handle_load_from_file(HashTable* hash_table) {
    char filename[256];
    printf("Digite o nome do arquivo para carregar os concursos: ");
    scanf("%s", filename);

    load_concursos_from_file(hash_table, filename);
    printf("Concursos carregados de %s.\n", filename);
}

void handle_display_statistics(HashTable* hash_table) {
    int choice, n, year, number;

    printf("Menu de Estatísticas:\n");
    printf("1. Contar frequência de um número específico\n");
    printf("2. Exibir os N números mais frequentes\n");
    printf("3. Exibir os N números menos frequentes\n");
    printf("4. Contar concursos em um ano específico\n");
    printf("Digite sua escolha: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Digite o número para contar a frequência: ");
            scanf("%d", &number);
            printf("O número %d foi sorteado %d vezes.\n", number, count_number_frequency(hash_table, number));
            break;
        case 2:
            printf("Digite N para os N números mais frequentes: ");
            scanf("%d", &n);
            display_top_n_numbers(hash_table, n, 1);
            break;
        case 3:
            printf("Digite N para os N números menos frequentes: ");
            scanf("%d", &n);
            display_top_n_numbers(hash_table, n, 0);
            break;
        case 4:
            printf("Digite o ano para contar os concursos: ");
            scanf("%d", &year);
            printf("Houve %d concursos em %d.\n", count_concursos_in_year(hash_table, year), year);
            break;
        default:
            printf("Escolha inválida.\n");
            break;
    }
}