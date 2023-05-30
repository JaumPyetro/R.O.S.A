#include "bibliotecas.h"
#include <stdio.h>
#include <string.h>

void Regulamento() {
  printf("\n");
  FILE *arquivo = fopen("Regulamento.txt", "r");
  if (arquivo == NULL) {
    printf("Lamentamos, mas não conseguimos encontrar o regulamento. Por favor, entre em contato conosco pelo email jpan@cesar.school para obter assistência.\n");
    return;
  }

  char linha[1000];
  while (fgets(linha, sizeof(linha), arquivo)) {
    printf("%s", linha);
  }

  fclose(arquivo);
  printf("\n");
  printf("\nPressione 1 para voltar ao menu ou 0 para sair: ");
  int opcao;
  scanf("%d", &opcao);

  while (opcao != 0 && opcao != 1) {
    printf("\n");
    printf("Opcao invalida! Digite novamente: ");
    scanf("%d", &opcao);
  }

  if (opcao == 1) {
    printf("\n");
    main(); // Chama o menu principal novamente
  } else {
    printf("\n");
    printf("Saindo do programa...\n");
  }
}

void criarContaResidente() {
  char email[100];
  char senha[9];

  printf("\nDigite o email do residente: ");
  scanf("%s", email);

  // Verifica se o email possui o domínio correto
  if (strstr(email, "@cesar.school") == NULL) {
    printf("Email invalido! O email deve ter o dominio '@cesar.school'.\n");
    return criarContaResidente();
  }

  printf("Digite a senha (8 caracteres): ");
  scanf("%s", senha);

  // Verifica o tamanho da senha
  if (strlen(senha) != 8) {
    printf("Senha invalida! A senha deve ter exatamente 8 caracteres.\n");
    return criarContaResidente();
  }

  FILE *arquivo = fopen("contas_residente.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo 'contas_residente.txt'!\n");
    return;
  }

  fprintf(arquivo, "%s %s\n", email, senha);
  fclose(arquivo);

  printf("Conta de residente criada com sucesso!\n");
}

void criarContaReceptor() {
  char email[100];
  char senha[9];

  printf("\nDigite o email do receptor: ");
  scanf("%s", email);

  // Verifica se o email possui o domínio correto
  if (strstr(email, "@cesar.school") == NULL) {
    printf("Email invalido! O email deve ter o dominio '@cesar.school'.\n");
    return criarContaReceptor();
  }

  printf("Digite a senha (8 caracteres): ");
  scanf("%s", senha);

  // Verifica o tamanho da senha
  if (strlen(senha) != 8) {
    printf("Senha invalida! A senha deve ter exatamente 8 caracteres.\n");
    return criarContaReceptor();
  }

  FILE *arquivo = fopen("contas_receptor.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo 'contas_receptor.txt'!\n");
    return;
  }

  fprintf(arquivo, "%s %s\n", email, senha);
  fclose(arquivo);

  printf("Conta de receptor criada com sucesso!\n");
}

void criarConta(char tipoConta[]) {
  if (strcmp(tipoConta, "residente") == 0) {
    criarContaResidente();
  } else if (strcmp(tipoConta, "receptor") == 0) {
    criarContaReceptor();
  } else {
    printf("Tipo de conta invalido!\n");
  }
}

void loginResidente() {
  char email[100];
  char senha[9];

  printf("\nDigite o email do residente: ");
  scanf("%s", email);

  // Verifica se o email possui o domínio correto
  if (strstr(email, "@cesar.school") == NULL) {
    printf("Email invalido! O email deve ter o dominio '@cesar.school'.\n");
    return loginResidente();
  }

  printf("Digite a senha: ");
  scanf("%s", senha);

  FILE *arquivo = fopen("contas_residente.txt", "r");
  if (arquivo == NULL) {
    printf("Por favor, solicite ao Gestor para que crie uma conta\n");
    return;
  }

  char linha[100];
  int loginValido = 0;

  while (fgets(linha, sizeof(linha), arquivo)) {
    char emailArquivo[100];
    char senhaArquivo[9];

    sscanf(linha, "%s %s", emailArquivo, senhaArquivo);

    if (strcmp(email, emailArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
      loginValido = 1;
      break;
    }
  }

  fclose(arquivo);

  if (loginValido) {
    printf("Login de residente bem-sucedido!\n");
  } else {
    printf("Email ou senha invalidos!\n");
    return loginResidente();
  }
}

void loginReceptor() {
  char email[100];
  char senha[9];

  printf("\nDigite o email do receptor: ");
  scanf("%s", email);

  // Verifica se o email possui o domínio correto
  if (strstr(email, "@cesar.school") == NULL) {
    printf("Email invalido! O email deve ter o dominio '@cesar.school'.\n");
    return loginReceptor();
  }

  printf("Digite a senha: ");
  scanf("%s", senha);

  FILE *arquivo = fopen("contas_receptor.txt", "r");
  if (arquivo == NULL) {
    printf("Por favor, solicite ao Gestor para que crie uma conta\n");
    return;
  }

  char linha[100];
  int loginValido = 0;

  while (fgets(linha, sizeof(linha), arquivo)) {
    char emailArquivo[100];
    char senhaArquivo[9];

    sscanf(linha, "%s %s", emailArquivo, senhaArquivo);

    if (strcmp(email, emailArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
      loginValido = 1;
      break;
    }
  }

  fclose(arquivo);

  if (loginValido) {
    printf("Login de receptor bem-sucedido!\n");
  } else {
    printf("Email ou senha invalidos!\n");
    return loginReceptor();
  }
}

void loginGestor() {
  char usuario[100];
  char senha[9];

  printf("\nDigite o usuario: ");
  scanf("%s", usuario);

  printf("Digite a senha: ");
  scanf("%s", senha);

  if (strcmp(usuario, "admin") == 0 && strcmp(senha, "12345") == 0) {
    printf("Login de gestor bem-sucedido!\n");

    int opcao;
    do {
      printf("\nEscolha uma opcao:\n");
      printf("1. Criar conta\n");
      printf("0. Sair\n");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1: {
        char tipoConta[20];
        printf("\nEscolha o tipo de conta a criar (residente ou receptor): ");
        scanf("%s", tipoConta);
        criarConta(tipoConta);
        break;
      }
      case 0:
        printf("Voltando ao menu de login...\n");
        break;
      default:
        printf("Opcao invalida!\n");
        break;
      }
    } while (opcao != 0);
  } else {
    printf("Usuario ou senha invalidos!\n");
  }
}

void login() {
  int opcao;
  printf("Escolha uma opcao:\n");
  printf("1. Login Residente\n");
  printf("2. Login Receptor\n");
  printf("3. Login Gestor\n");
  scanf("%d", &opcao);

  switch (opcao) {
  case 1:
    loginResidente();
    break;
  case 2:
    loginReceptor();
    break;
  case 3:
    loginGestor();
    break;
  default:
    printf("Opcao invalida!\n");
    break;
  }
}

