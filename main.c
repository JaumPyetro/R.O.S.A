#include "bibliotecas.h"
#include <stdio.h>

int main() {
  int opcao;
  printf("BEM VINDO AO PROGRAMA ROSA\n");

  int continuar = 1; // Variável para controlar a execução do loop

  while (continuar) {
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
        Regulamento(&continuar); // Passo a variável "continuar" como parâmetro
        break;
      case 0:
        printf("Saindo do programa...\n");
        continuar = 0; // Define a variável "continuar" como 0 para encerrar o loop
        break;
      default:
        printf("Opcao invalida!\n");
        break;
    }
  }
  
  return 0;
}
