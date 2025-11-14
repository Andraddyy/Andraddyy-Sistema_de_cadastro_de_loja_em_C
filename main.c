#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100 // Definindo o tamanho máximo para o vetor de produtos
// Estrutura para armazenar as informações do produto
typedef struct {
  int id;
  char nome[50];
  char categoria[30];
  float preco;
} Produto;
Produto lista[MAX];
int total = 0; // Contador para o número de produtos cadastrados



// Função para comparar strings de forma case-insensitive
int comparaCaseInsensitive(const char *str1, const char *str2) {
  while (*str1 && *str2) {
    if (tolower(*str1) != tolower(*str2)) {
      return 0;
    }
    str1++;
    str2++;
  }
  return (*str1 == *str2);
}



// Função para gerar o próximo ID (incremental)
int gerarID() {
  return total + 1; // Gera um ID incremental baseado no total de produtos
}



// Função para verificar se o produto já existe (verifica duplicidade pelo nome)
int verificarDuplicata(char nome[]) {
  for (int i = 0; i < total; i++) {
    if (comparaCaseInsensitive(lista[i].nome, nome)) {
      return 1; // Produto já cadastrado
    }
  }
  return 0; // Não encontrado
}



// Função para ordenar os produtos pelo nome (A-Z)
void ordenarPorNomeAZ() {
  for (int i = 0; i < total - 1; i++) {
    for (int j = i + 1; j < total; j++) {
      if (strcmp(lista[i].nome, lista[j].nome) > 0) {
        Produto temp = lista[i];
        lista[i] = lista[j];
        lista[j] = temp;
      }
    }
  }
}



// Função para ordenar os produtos pelo nome (Z-A)
void ordenarPorNomeZA() {
  for (int i = 0; i < total - 1; i++) {
    for (int j = i + 1; j < total; j++) {
      if (strcmp(lista[i].nome, lista[j].nome) < 0) {
        Produto temp = lista[i];
        lista[i] = lista[j];
        lista[j] = temp;
      }
    }
  }
}



// Função para ordenar os produtos pelo preço (menor → maior)
void ordenarPorPrecoCrescente() {
  for (int i = 0; i < total - 1; i++) {
    for (int j = i + 1; j < total; j++) {
      if (lista[i].preco > lista[j].preco) {
        Produto temp = lista[i];
        lista[i] = lista[j];
        lista[j] = temp;
      }
    }
  }
}



// Função para ordenar os produtos pelo preço (maior → menor)
void ordenarPorPrecoDecrescente() {
  for (int i = 0; i < total - 1; i++) {
    for (int j = i + 1; j < total; j++) {
      if (lista[i].preco < lista[j].preco) {
        Produto temp = lista[i];
        lista[i] = lista[j];
        lista[j] = temp;
      }
    }
  }
}



// Função para exibir os produtos cadastrados
void listarProdutos() {
  if (total == 0) {
    printf("Nenhum produto cadastrado.\n");
    return;
  }
  printf("\n--- Lista de Produtos ---\n");
  for (int i = 0; i < total; i++) {
    printf("ID: %d\n", lista[i].id);
    printf("Nome: %s\n", lista[i].nome);
    printf("Categoria: %s\n", lista[i].categoria);
    printf("Preço: %.2f\n", lista[i].preco);
    printf("------------------------\n");
  }
}



// Função para buscar um produto por nome
void buscarProdutoPorNome() {
  char nome[50];
  printf("Digite o nome do produto a ser buscado: ");
  fgets(nome, 50, stdin);
  nome[strcspn(nome, "\n")] = '\0'; // Remover o '\n' da string
  printf("\n--- Resultado da busca ---\n");
  for (int i = 0; i < total; i++) {
    if (comparaCaseInsensitive(lista[i].nome, nome)) {
      printf("ID: %d\n", lista[i].id);
      printf("Nome: %s\n", lista[i].nome);
      printf("Categoria: %s\n", lista[i].categoria);
      printf("Preço: %.2f\n", lista[i].preco);
      printf("------------------------\n");
      return;
    }
  }
  printf("Produto não encontrado.\n");
}



// Função para inserir um novo produto
void inserirProduto() {
  if (total >= MAX) {
    printf("Limite de produtos alcançado!\n");
    return;
  }
  Produto p;
  p.id = gerarID(); // ID automático
  getchar(); // Limpar o buffer de entrada
  printf("Digite o nome do produto: ");
  fgets(p.nome, 50, stdin);
  p.nome[strcspn(p.nome, "\n")] = '\0'; // Remover o '\n' da string
  if (verificarDuplicata(p.nome)) {
    printf("Produto com o mesmo nome já cadastrado!\n");
    return;
  }
  printf("Digite a categoria do produto: ");
  fgets(p.categoria, 30, stdin);
  p.categoria[strcspn(p.categoria, "\n")] = '\0'; // Remover o '\n'
  printf("Digite o preço do produto: ");
  scanf("%f", &p.preco);
  lista[total++] = p; // Adiciona o novo produto à lista
  printf("Produto inserido com sucesso!\n");
}



// Função para salvar os dados em um arquivo CSV
void exportarParaCSV() {
  FILE *fp = fopen("produtos.csv", "w");
  if (fp == NULL) {
    printf("Erro ao criar arquivo CSV!\n");
    return;
  }
  for (int i = 0; i < total; i++) {
    fprintf(fp, "%d,%s,%s,%.2f\n", lista[i].id, lista[i].nome, lista[i].categoria, lista[i].preco);
  }
  fclose(fp);
  printf("Dados exportados para produtos.csv com sucesso!\n");
}



// Função principal (menu)
int main() {
  int opcao;
  do {
    printf("\n===== MENU CADASTRO DE PRODUTOS =====\n");
    printf("1 - Inserir novo produto\n");
    printf("2 - Listar produtos\n");
    printf("3 - Buscar produto por nome\n");
    printf("4 - Ordenar produtos por nome (A-Z)\n");
    printf("5 - Ordenar produtos por nome (Z-A)\n");
    printf("6 - Ordenar produtos por preço (menor -> maior)\n");
    printf("7 - Ordenar produtos por preço (maior -> menor)\n");
    printf("8 - Exportar dados para CSV\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    switch (opcao) {
    
      case 1: inserirProduto(); break;

      case 2: listarProdutos(); break;

      case 3: buscarProdutoPorNome(); break;

      case 4: ordenarPorNomeAZ(); break;

      case 5: ordenarPorNomeZA(); break;

      case 6: ordenarPorPrecoCrescente(); break;

      case 7: ordenarPorPrecoDecrescente(); break;

      case 8: exportarParaCSV(); break;

      case 0: printf("Saindo...\n"); break;

      default: printf("Opção inválida!\n");
    }
  } while (opcao != 0);
  return 0;
}
