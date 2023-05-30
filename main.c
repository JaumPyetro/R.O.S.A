#include "bibliotecas.h"
#include <stdio.h>

int main() {
  int opcao;
  printf("BEM VINDO AO PROGRAMA ROSA\n");

  do {
    printf("\nEscolha uma opcao:\n");
    printf("1. Login\n");
    printf("2. Regulamento\n");
    printf("0. Sair\n");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      login();
      break;
    case 2:
      Regulamento();
      opcao = 1; // Definir opção como 1 para voltar ao menu principal
      break;
    case 0:
      printf("Saindo do programa...\n");
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  } while (opcao != 0);

  return 0;
}

