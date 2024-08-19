# Gerenciador de Concursos da Mega-Sena

## Autores:

- Gabriel Fontineli Dantas
- Matheus Freitas

Este projeto é um sistema para gerenciar concursos da Mega-Sena, utilizando uma tabela de dispersão (hash table) para armazenar e acessar os resultados dos concursos. O sistema é capaz de realizar operações básicas como inserção, busca, remoção de concursos e também calcular e apresentar estatísticas relevantes sobre os números sorteados.

## Funcionalidades

1. **Inserir Concurso**:
   - Permite ao usuário inserir um novo concurso na tabela de dispersão.
   - Verifica se o número do concurso já existe para evitar duplicações.
   - Garante que os números sorteados estejam entre 1 e 60.
   - Garante que não haja números repetidos dentro de um mesmo concurso.

2. **Buscar Concurso**:
   - Permite ao usuário buscar um concurso específico na tabela usando o número do concurso.
   - Retorna a data do sorteio e os números sorteados.

3. **Remover Concurso**:
   - Permite ao usuário remover um concurso da tabela de dispersão usando o número do concurso.
   - Garante que o concurso seja excluído corretamente da tabela.

4. **Exibir Todos os Concursos**:
   - Exibe todos os concursos armazenados na tabela de dispersão.
   - Mostra o número do concurso, a data do sorteio e os números sorteados.

5. **Carregar Concursos de um Arquivo**:
   - Permite carregar concursos a partir de um arquivo CSV ou TSV.
   - O arquivo deve conter resultados históricos dos sorteios da Mega-Sena.

6. **Exibir Estatísticas**:
   - Contagem de frequência de um número específico.
   - Exibição dos N números mais frequentes.
   - Exibição dos N números menos frequentes.
   - Contagem de concursos realizados em um ano específico.

## Estrutura do Projeto

- **src/**: Contém os arquivos de código fonte do projeto.
- **include/**: Contém os arquivos de cabeçalho (.h) usados no projeto.
- **bin/**: Contém o executável do projeto.
- **data/**: Contém arquivos de dados (CSV ou TSV) usados para carregar concursos.

## Requisitos

- Compilador C (gcc, por exemplo).
- Makefile para compilar o projeto.
- Arquivo de dados no formato CSV ou TSV para carregar concursos (opcional).

## Compilação e Execução

Para compilar o projeto, execute o comando:

```bash
make
```

Isso gerará um executável na pasta bin/ chamado mega_sena_manager.

Para executar o programa, use:

```bash
./bin/mega_sena_manager
```

Exemplo de Uso

Ao executar o programa, você verá o seguinte menu:

```bash
Gerenciador da Mega-Sena
1. Inserir Concurso
2. Buscar Concurso
3. Remover Concurso
4. Exibir Todos os Concursos
5. Carregar Concursos de um Arquivo
6. Exibir Estatísticas
0. Sair
Digite sua escolha: 
```
Inserir Concurso

Escolha a opção 1 e insira os dados conforme solicitado. O sistema garantirá que os números estejam na faixa correta e que não haja duplicação de concursos.

Carregar Concursos de um Arquivo

Escolha a opção 5, insira o nome do arquivo (CSV ou TSV) que contém os resultados históricos, e os concursos serão carregados automaticamente no sistema.

Formato de Arquivo de Dados

O arquivo deve ter uma linha por concurso, com o número do concurso, a data do sorteio e os 6 números sorteados, separados por vírgulas (CSV) ou tabulação (TSV).

```csv
2756,01-08-2024,1,46,13,18,6,43
2755,30-07-2024,58,7,17,33,41,13
2754,27-07-2024,55,10,44,14,56,58
```

