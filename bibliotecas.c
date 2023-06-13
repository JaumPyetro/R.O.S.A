#include "bibliotecas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//
#define MAX_LINE_LENGTH 1000
#define MAX_NAME_LENGTH 100
#define ACCESS_KEY_LENGTH 6
#define TIME_STRING_LENGTH 20
#define MAX_RESIDENTES 100
#define MAX_LENGTH 100

void aplicativoRosa() {
  int opcao;

  printf("Escolha uma opcao:\n");
  printf("1. Login\n");
  printf("2. Regulamento\n");
  printf("3. Sair do aplicativo\n");

  printf("\n-> ");

  scanf("%d", &opcao);

  switch (opcao) {
  case 1:
    homeLogin();
    break;
  case 2:
    exibirRegulamento();
    break;
  case 3:
    printf("Saindo do aplicativo...");
    break;
  default:
    printf("Opcao invalida!\n");
    break;
  }
}

void exibirRegulamento() {
  FILE *arquivo;
  char linha[100];
  int opcao;

  arquivo = fopen("regulamento.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo regulamento.txt.\n");
    return;
  }

  printf("--- REGULAMENTO ---\n\n\n");

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    printf("%s", linha);
  }

  fclose(arquivo);

  printf("\n\nDigite 0 para voltar\n");
  printf("\n-> ");
  scanf("%d", &opcao);

  if (opcao == 0) {
    printf("\n");
    aplicativoRosa(); // Volta para o menu do aplicativo
  }
}

void homeLogin() {
  int opcao;

  printf("Escolha uma opção de login:\n");
  printf("1. Login Residente\n");
  printf("2. Login Preceptor\n");
  printf("3. Login Gestor\n");
  printf("\n-> ");
  scanf("%d", &opcao);

  switch (opcao) {
  case 1:
    loginResidente();
    break;
  case 2:
    loginPreceptor();
    break;
  case 3:
    loginGestor();
    break;
  default:
    printf("Opcao invalida!\n");
    break;
  }
}

void loginGestor() {
  char usuario[20];
  char senha[20];

  printf("Login do Gestor\n");
  printf("Usuario: ");
  scanf("%s", usuario);

  printf("Senha: ");
  scanf("%s", senha);

  if (strcmp(usuario, "admin") == 0 && strcmp(senha, "12345") == 0) {
    printf("Login do Gestor bem-sucedido!\n");
    homeGestor(); // Chama a função homeGestor após o login bem-sucedido
  } else {
    printf("Usuario ou senha incorretos!\n");
  }
}

void homeGestor() {
  int opcao;

  printf("Opcoes do Gestor:\n");
  printf("1. Criar conta\n");
  printf("2. Lista de Residentes\n");
  printf("3. Lista de Preceptores\n");
  printf("0. Sair\n");
  printf("\n-> ");
  scanf("%d", &opcao);

  switch (opcao) {
  case 1:
    criarConta();
    break;
  case 0:
    homeLogin();
    break;
  case 2:
    ListaDeResidentesGestor();
    break;
  case 3:
    imprimirPreceptores();
    break;
  default:
    printf("Opcao invalida!\n");
    break;
  }
}

void criarConta() {
  int opcao;

  printf("Criar conta:\n");
  printf("1. Residente\n");
  printf("2. Preceptor\n");

  scanf("%d", &opcao);

  switch (opcao) {
  case 1:
    criarContaResidente();
    break;
  case 2:
    criarContaPreceptor();
    break;
  default:
    printf("Opcao invalida!\n");
    break;
  }
}

void criarContaResidente() {
  char nome[50];
  char cpf[12];
  char senha[20];
  char confirmacaoSenha[20];
  char curso[50];
  char chaveAcesso[7]; // Alterado para 7 para acomodar 6 dígitos e o caractere
                       // nulo
  int i;

  printf("Criar conta de Residente\n");

  printf("Nome completo: ");
  getchar(); // Limpar o buffer do teclado
  fgets(nome, sizeof(nome), stdin);
  nome[strcspn(nome, "\n")] = '\0'; // Remover a quebra de linha

  printf("CPF: ");
  scanf("%s", cpf);

  printf("Senha: ");
  scanf("%s", senha);

  printf("Confirmar senha: ");
  scanf("%s", confirmacaoSenha);

  if (strcmp(senha, confirmacaoSenha) != 0) {
    printf("As senhas nao correspondem. A conta nao foi criada.\n");
    return;
  }

  printf("Residência: ");
  getchar(); // Limpar o buffer do teclado
  fgets(curso, sizeof(curso), stdin);
  curso[strcspn(curso, "\n")] = '\0'; // Remover a quebra de linha

  // Gerar chave de acesso aleatória com 6 dígitos
  srand(time(NULL));
  for (i = 0; i < 6; i++) {
    chaveAcesso[i] = '0' + rand() % 10;
  }
  chaveAcesso[i] = '\0';

  FILE *arquivo = fopen("residenteDados.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo residenteDados.txt.\n");
    return;
  }

  fprintf(arquivo, "Nome: %s\n", nome);
  fprintf(arquivo, "CPF: %s\n", cpf);
  fprintf(arquivo, "Senha: %s\n", senha);
  fprintf(arquivo, "Curso: %s\n", curso);
  fprintf(arquivo, "Chave de Acesso: %s\n", chaveAcesso);
  fprintf(arquivo, "\n----------------------------------------\n");

  fclose(arquivo);

  // Adicione este código para salvar a chave de acesso junto com o nome do
  // residente no arquivo residenteChaves.txt
  FILE *file = fopen("residenteChaves.txt", "a");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo residenteChaves.txt.\n");
    return;
  }

  fprintf(file, "%s\n", nome);
  fprintf(file, "%s\n", chaveAcesso);

  fclose(file);

  printf("Conta de Residente criada com sucesso!\n");
}

void criarContaPreceptor() {
  char cpf[12];
  char senha[20];
  char confirmacaoSenha[20];
  char nome[50];

  printf("Criar conta de Preceptor\n");

  printf("CPF: ");
  scanf("%s", cpf);

  printf("Nome completo: ");
  getchar(); // Limpar o buffer do teclado
  fgets(nome, sizeof(nome), stdin);
  nome[strcspn(nome, "\n")] = '\0'; // Remover a quebra de linha

  printf("Senha: ");
  scanf("%s", senha);

  printf("Confirmar senha: ");
  scanf("%s", confirmacaoSenha);

  if (strcmp(senha, confirmacaoSenha) != 0) {
    printf("As senhas nao correspondem. A conta nao foi criada.\n");
    return;
  }

  FILE *arquivo = fopen("preceptorDados.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo preceptorDados.txt.\n");
    return;
  }

  fprintf(arquivo, "CPF: %s\n", cpf);
  fprintf(arquivo, "Nome: %s\n", nome);
  fprintf(arquivo, "Senha: %s\n", senha);
  fprintf(arquivo, "\n----------------------------------------\n");

  fclose(arquivo);

  printf("Conta de Preceptor criada com sucesso!\n");
}

void loginPreceptor() {
  char cpf[12];
  char senha[20];

  printf("Login Preceptor\n");
  printf("CPF: ");
  scanf("%11s", cpf);
  printf("Senha: ");
  scanf("%19s", senha);

  FILE *arquivo = fopen("preceptorDados.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo preceptorDados.txt.\n");
    return;
  }

  char linha[100];
  char cpfArquivo[12];
  char senhaArquivo[20];
  char nome[100];
  int encontrado = 0;

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (strstr(linha, "CPF:") ==
        linha) { // Verifica se a linha começa com "CPF:"
      sscanf(linha, "CPF: %11s", cpfArquivo);
      fgets(linha, sizeof(linha),
            arquivo); // Lê a próxima linha após o CPF encontrado

      fgets(linha, sizeof(linha), arquivo); // Lê a senha

      linha[strcspn(linha, "\n")] = '\0';
      strcpy(senhaArquivo, linha + 7); // Ignora "Senha: "

      if (strcmp(cpf, cpfArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
        encontrado = 1;
        fgets(linha, sizeof(linha), arquivo); // Lê o nome
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(nome, linha + 6); // Ignora "Nome: "
        break;
      }
    }
  }

  fclose(arquivo);

  if (encontrado) {
    printf("Login realizado com sucesso!\n");
    homePreceptor(nome, cpf); // Passa o nome e o CPF do preceptor como
                              // argumentos para a função homePreceptor()
  } else {
    printf("CPF ou senha inválidos!\n");
  }
}

void homePreceptor(const char *nome, const char *cpf) {
  printf("\n--- Home Preceptor ---\n");

  FILE *arquivo = fopen("preceptorDados.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo preceptorDados.txt.\n");
    return;
  }

  char linha[100];
  char cpfArquivo[12];

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    sscanf(linha, "CPF: %11s", cpfArquivo);
    if (strcmp(cpf, cpfArquivo) == 0) {
      fgets(linha, sizeof(linha),
            arquivo);      // Lê a próxima linha após o CPF encontrado
      printf("%s", linha); // Imprime a linha de baixo
      break;
    }
  }

  fclose(arquivo);

  int opcao;
  do {
    printf("\nOpções:\n");
    printf("1. Lista de residentes\n");
    printf("0. Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("\n--- Lista de Residentes ---\n");
      ListaDeResidentes();
    case 0:
      printf("\nSaindo da sua conta...\n");
      printf("\nVoltando para login\n\n");
      homeLogin();
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }
  } while (opcao != 4);
}

typedef struct {
  char nome[100];
  char curso[100];
} Residente;

int comparaResidente(const void *a, const void *b) {
  Residente *residenteA = (Residente *)a;
  Residente *residenteB = (Residente *)b;
  return strcmp(residenteA->curso, residenteB->curso);
}

void feedback(char *nome) {
  printf("Digite o feedback para %s: ", nome);
  char feedback[1000];
  scanf(" %[^\n]", feedback);

  FILE *arquivo = fopen("feedback.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo feedback.txt.\n");
    return;
  }

  fprintf(arquivo, "Feedback para %s:\n%s\n\n", nome, feedback);

  fclose(arquivo);

  printf("Feedback salvo com sucesso.\n");
}

void ListaDeResidentes() {
  FILE *arquivo = fopen("residenteDados.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo residenteDados.txt.\n");
    return;
  }

  Residente residentes[MAX_RESIDENTES];
  int numResidentes = 0;

  char linha[100];
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (strstr(linha, "Nome:") ==
        linha) { // Verifica se a linha começa com "Nome:"
      strcpy(residentes[numResidentes].nome, linha + 6); // Ignora "Nome: "
      residentes[numResidentes]
          .nome[strcspn(residentes[numResidentes].nome, "\n")] = '\0';

      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "Curso:") ==
            linha) { // Verifica se a linha começa com "Curso:"
          strcpy(residentes[numResidentes].curso,
                 linha + 7); // Ignora "Curso: "
          residentes[numResidentes]
              .curso[strcspn(residentes[numResidentes].curso, "\n")] = '\0';
          break;
        }
      }

      numResidentes++;
    }
  }

  fclose(arquivo);

  qsort(residentes, numResidentes, sizeof(Residente), comparaResidente);

  char cursoAnterior[100] = "";
  for (int i = 0; i < numResidentes; i++) {
    if (strcmp(cursoAnterior, residentes[i].curso) != 0) {
      printf("\nResidência %s\n\n", residentes[i].curso);
      strcpy(cursoAnterior, residentes[i].curso);
    }

    printf("%d. Nome: %s\n", i + 1, residentes[i].nome);
  }

  printf("\nDigite o número do residente para ver mais detalhes: ");
  int escolha;
  scanf("%d", &escolha);
  escolha--;

  if (escolha >= 0 && escolha < numResidentes) {
    int opcao;
    do {
      printf("\n--- Avaliação ---\n");
      printf("1. Monitoramento\n");
      printf("2. Feedback\n");
      printf("3. Ficha avaliativa\n");
      printf("4. Sair\n");
      printf("\n-> ");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1:
        printf("\n--- Monitoramento ---\n");
        printf("Nome: %s\n", residentes[escolha].nome);
        printf("Curso: %s\n", residentes[escolha].curso);
        calendario(residentes[escolha].nome);
        showTotalProgress(residentes[escolha].nome);
        break;
      case 2:
        printf("\n--- Feedback ---\n");
        feedback(residentes[escolha].nome);
        break;
      case 3:
        fichaAvaliativa(residentes[escolha].nome, residentes[escolha].curso);
        break;
      case 4:
        break;
      default:
        printf("Opção inválida.\n");
        break;
      }
    } while (opcao != 4);
  } else {
    printf("Escolha inválida.\n");
  }
}

int loginResidente() {
  char cpfEntrada[12];
  char senhaEntrada[20];

  printf("CPF: ");
  scanf("%s", cpfEntrada);

  printf("Senha: ");
  scanf("%s", senhaEntrada);

  FILE *arquivo = fopen("residenteDados.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo residenteDados.txt.\n");
    return 0;
  }

  char linha[200];
  char nome[50];
  char cpf[15];
  char senha[25];
  int residenteEncontrado = 0;

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (strncmp(linha, "Nome: ", 6) == 0) {
      strcpy(nome, linha + 6);
      nome[strcspn(nome, "\n")] = '\0'; // Remover a quebra de linha
    } else if (strncmp(linha, "CPF: ", 5) == 0) {
      strcpy(cpf, linha + 5);
      cpf[strcspn(cpf, "\n")] = '\0'; // Remover a quebra de linha
      if (strcmp(cpf, cpfEntrada) == 0) {
        residenteEncontrado = 1;
      }
    } else if (strncmp(linha, "Senha: ", 7) == 0 && residenteEncontrado) {
      strcpy(senha, linha + 7);
      senha[strcspn(senha, "\n")] = '\0'; // Remover a quebra de linha
      if (strcmp(senha, senhaEntrada) == 0) {
        fclose(arquivo);
        homeResidente(nome);
        return 1;
      } else {
        residenteEncontrado = 0;
      }
    }
  }

  fclose(arquivo);
  return 0;
}

void homeResidente(char *nomeResidente) {
  int opcao;
  char accessKey[11]; // Mova a declaração da variável accessKey para aqui
  FILE *file = fopen("residenteChaves.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo residenteChaves.txt.\n");
    return;
  }

  char line[100];
  char name[50];
  int residentFound = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    strcpy(name, line);
    name[strcspn(name, "\n")] = '\0'; // Remover a quebra de linha
    if (strcmp(name, nomeResidente) == 0) {
      residentFound = 1;
      fgets(line, sizeof(line), file);
      strcpy(accessKey, line);
      accessKey[strcspn(accessKey, "\n")] = '\0'; // Remover a quebra de linha
      break;
    }
  }

  fclose(file);
  do {
    printf("\n--- Menu do Residente ---\n");
    printf("\nNome: %s\n\n", nomeResidente);
    printf("\n-- INFORMAÇÕES --\n");
    printf("1. Chave de Acesso\n");
    printf("2. Presença\n");
    printf("3. Progresso\n");
    printf("4. Avaliação\n");
    printf("5. Feedback\n");
    printf("0. Sair\n");
    printf("\n-> ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      FILE *file = fopen("residenteChaves.txt", "r");
      if (file == NULL) {
        printf("Erro ao abrir o arquivo residenteChaves.txt.\n");
        break;
      }

      char line[100];
      char name[50];
      int residentFound = 0;

      while (fgets(line, sizeof(line), file) != NULL) {
        strcpy(name, line);
        name[strcspn(name, "\n")] = '\0'; // Remover a quebra de linha
        if (strcmp(name, nomeResidente) == 0) {
          residentFound = 1;
          fgets(line, sizeof(line), file);
          strcpy(accessKey, line);
          accessKey[strcspn(accessKey, "\n")] =
              '\0'; // Remover a quebra de linha
          break;
        }
      }

      fclose(file);

      if (residentFound) {
        printf("Chave de acesso: %s\n", accessKey);
      } else {
        printf("Nao foi possivel encontrar sua chave de acesso.\n");
      }
      break;
    }
    case 2: {
      calendario(nomeResidente);
      printf("\n\n--- REGISTRO DE PRESENÇA ---\n");
      registro(nomeResidente, accessKey);
      break;
    }

    case 3: {

      showTotalProgress(nomeResidente);
      break;
    }
    case 4: {
      printf("\n\n--- FICHAS DE AVALIAÇÃO ---\n");
      imprimirFichaAvaliacao(nomeResidente);
      break;
    }
    case 5: {
      printf("\n\n--- FEEDBACK ---\n");
      imprimirFeedback(nomeResidente);
      break;
    }
    case 0: {
      printf("Saindo...\n");
      break;
    }
    default: {
      printf("Opcao invalida.\n");
    }
    }
  } while (opcao != 0);
}

void calendario(char *nomeResidente) {

  int dias = 30;
  int diaSemana = 2; // 0 = Domingo, 1 = Segunda-feira, ..., 6 = Sábado
  int tempoPermanencia[dias + 1];
  memset(tempoPermanencia, 0, sizeof(tempoPermanencia));

  FILE *file = fopen("residenteChaves.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo residenteChaves.txt.\n");
    return;
  }

  char line[100];
  char name[55];
  char accessKey[11];
  int residentFound = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    strcpy(name, line);
    name[strcspn(name, "\n")] = '\0'; // Remover a quebra de linha
    if (strcmp(name, nomeResidente) == 0) {
      residentFound = 1;
      fgets(line, sizeof(line), file);
      strcpy(accessKey, line);
      accessKey[strcspn(accessKey, "\n")] = '\0'; // Remover a quebra de linha
      break;
    }
  }

  fclose(file);

  if (residentFound) {
    FILE *presenceFile = fopen("presencaResidente.txt", "r");
    if (presenceFile == NULL) {
      printf("Erro ao abrir o arquivo presencaResidente.txt.\n");
      return;
    }

    char presenceAccessKey[ACCESS_KEY_LENGTH + 1];
    char entryOrExit;
    int seconds;
    int year, month, day;

    while (fscanf(presenceFile, "%6s %c %d-%d-%d", presenceAccessKey,
                  &entryOrExit, &year, &month, &day) == 5) {
      fgets(line, sizeof(line), presenceFile); // Ignorar a hora
      if (strcmp(presenceAccessKey, accessKey) == 0 && entryOrExit == 'S') {
        fscanf(presenceFile, "%d", &seconds);
        tempoPermanencia[day] += seconds;
      }
    }

    fclose(presenceFile);
  }

  printf("\n    --- CALENDÁRIO ---\n");
  printf("Dom Seg Ter Qua Qui Sex Sab\n");

  for (int i = 0; i < diaSemana; i++) {
    printf("     ");
  }

  for (int dia = 1; dia <= dias; dia++) {
    if (tempoPermanencia[dia] == 0) {
      printf("\033[90m"); // Cinza
    } else if (tempoPermanencia[dia] >= 28740) {
      printf("\033[32m"); // Verde
    } else if (tempoPermanencia[dia] <= 1800) {
      printf("\033[31m"); // Vermelho
    } else {
      printf("\033[33m"); // Amarelo
    }

    printf("%3d ", dia);
    printf("\033[0m"); // Resetar cor

    if ((dia + diaSemana) % 7 == 0) {
      printf("\n");
    }
  }

  printf("\n");
}

void showTotalProgress(char *nomeResidente) {
  FILE *file = fopen("residenteChaves.txt", "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo residenteChaves.txt.\n");
    return;
  }

  char line[100];
  char name[55];
  char accessKey[11];
  int residentFound = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    strcpy(name, line);
    name[strcspn(name, "\n")] = '\0'; // Remover a quebra de linha
    if (strcmp(name, nomeResidente) == 0) {
      residentFound = 1;
      fgets(line, sizeof(line), file);
      strcpy(accessKey, line);
      accessKey[strcspn(accessKey, "\n")] = '\0'; // Remover a quebra de linha
      break;
    }
  }

  fclose(file);

  if (!residentFound) {
    printf("Nao foi possivel encontrar sua chave de acesso.\n");
    return;
  }

  FILE *presenceFile = fopen("presencaResidente.txt", "r");
  if (presenceFile == NULL) {
    printf("Erro ao abrir o arquivo presencaResidente.txt.\n");
    return;
  }

  char presenceAccessKey[ACCESS_KEY_LENGTH + 1];
  char entryOrExit;
  int seconds;
  int accessKeyFound = 0;
  int year, month, day;
  int totalSeconds = 0;

  while (fscanf(presenceFile, "%6s %c %d-%d-%d", presenceAccessKey,
                &entryOrExit, &year, &month, &day) == 5) {
    fgets(line, sizeof(line), presenceFile); // Ignorar a hora
    if (strcmp(presenceAccessKey, accessKey) == 0) {
      accessKeyFound = 1;
      if (entryOrExit == 'S') {
        fscanf(presenceFile, "%d", &seconds);
        totalSeconds += seconds;
      }
    }
  }

  fclose(presenceFile);

  if (!accessKeyFound) {
    printf("Não foi possível encontrar sua chave de acesso no arquivo "
           "presencaResidente.txt.\n");
  } else {
    int progress = totalSeconds / 63360;
    printf("[");
    for (int i = 0; i < progress; i++) {
      printf("#");
    }
    for (int i = progress; i < 10; i++) {
      printf(" ");
    }
    printf("]\n");

    div_t hours = div(totalSeconds, 3600);
    div_t minutes = div(hours.rem, 60);

    printf("Tempo total: %02d:%02d:%02d\n", hours.quot, minutes.quot,
           minutes.rem);
  }
}

void registro(char *nomeResidente, char *accessKey) {
  int dias = 30;
  int tempoPermanencia[dias + 1];
  memset(tempoPermanencia, 0, sizeof(tempoPermanencia));

  FILE *presenceFile = fopen("presencaResidente.txt", "r");
  if (presenceFile == NULL) {
    printf("Erro ao abrir o arquivo presencaResidente.txt.\n");
    return;
  }

  char line[100]; // Adicione esta linha para declarar a variável line
  char presenceAccessKey[ACCESS_KEY_LENGTH + 1];
  char entryOrExit;
  int seconds;
  int year, month, day;

  while (fscanf(presenceFile, "%6s %c %d-%d-%d", presenceAccessKey,
                &entryOrExit, &year, &month, &day) == 5) {
    fgets(line, sizeof(line), presenceFile); // Ignorar a hora
    if (strcmp(presenceAccessKey, accessKey) == 0 && entryOrExit == 'S') {
      fscanf(presenceFile, "%d", &seconds);
      tempoPermanencia[day] += seconds;
    }
  }

  fclose(presenceFile);

  FILE *file2 = fopen("registroResidente.txt", "r");
  if (file2 == NULL) {
    printf("Erro ao abrir o arquivo registroResidente.txt.\n");
    return;
  }

  char line2[100];
  char residencyProgram[50];
  char dayActivity[50];
  int infoFound = 0;

  for (int dia = 1; dia <= dias; dia++) {
    if (tempoPermanencia[dia] > 0) {
      fseek(file2, 0, SEEK_SET); // Voltar para o início do arquivo
      infoFound = 0;

      while (fgets(line2, sizeof(line2), file2) != NULL) {
        if (strncmp(line2, accessKey, strlen(accessKey)) == 0 &&
            sscanf(line2, "%*s %s %d-%d-%d %s", residencyProgram, &year, &month,
                   &day, dayActivity) == 5 &&
            day == dia) {
          infoFound = 1;
          break;
        }
      }

      if (infoFound) {
        printf("Dia %d: %dh %02dm %02ds\n", dia, tempoPermanencia[dia] / 3600,
               (tempoPermanencia[dia] / 60) % 60, tempoPermanencia[dia] % 60);
        printf("Programa de residência: %s\n", residencyProgram);
        printf("Atividade do dia: %s\n", dayActivity);
      } else {
        printf("Informações adicionais não encontradas para o dia %d.\n", dia);
      }
    }
  }

  fclose(file2);
}

void homeTotem() {
  char access_key[7];
  printf("Digite a chave de acesso de 6 dígitos: ");
  scanf("%s", access_key);
  FILE *f = fopen("residenteChaves.txt", "r");
  char line[256];
  int found = 0;
  char name[256];
  while (fgets(line, sizeof(line), f)) {
    line[strcspn(line, "\n")] = 0;
    if (strcmp(line, access_key) == 0) {
      found = 1;
      break;
    }
    strcpy(name, line);
  }
  fclose(f);
  if (found) {
    f = fopen("presencaResidente.txt", "r");
    int last_entry = 0;
    char last_entry_time[20];
    while (fgets(line, sizeof(line), f)) {
      if (strstr(line, access_key) != NULL) {
        if (strstr(line, " E ") != NULL) {
          last_entry = 1;
          strncpy(last_entry_time, strstr(line, " E ") + 3, 19);
        } else if (strstr(line, " S ") != NULL) {
          last_entry = 0;
        }
      }
    }
    fclose(f);
    f = fopen("presencaResidente.txt", "a");
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    if (last_entry) {
      fprintf(f, "%s S %d-%02d-%02d %02d:%02d:%02d\n", access_key,
              t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour,
              t->tm_min, t->tm_sec);
      printf("SAÍDA SALVA PARA %s\n", name);
      struct tm entry_time;
      strptime(last_entry_time, "%Y-%m-%d %H:%M:%S", &entry_time);
      time_t entry_time_t = mktime(&entry_time);
      int duration = difftime(now, entry_time_t);
      fprintf(f, "%d\n", duration);
    } else {
      fprintf(f, "%s E %d-%02d-%02d %02d:%02d:%02d\n", access_key,
              t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour,
              t->tm_min, t->tm_sec);
      printf("ENTRADA SALVA PARA %s\n", name);
    }
    fclose(f);

    // Questionamentos
    char programa_residencia[256];
    char atividade_dia[256];

    printf("Programa de residência "
           "(Médica/Multiprofissional/Enfermagem/Nutrição): ");
    scanf("%s", programa_residencia);

    printf("Atividade do dia (Teóricas/Práticas): ");
    scanf("%s", atividade_dia);

    // Salvando no arquivo de registro
    f = fopen("registroResidente.txt", "a");
    fprintf(f, "%s %s %d-%02d-%02d %s\n", access_key, programa_residencia,
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, atividade_dia);
    fclose(f);
  } else {
    printf("Chave de acesso inválida\n");
  }
}

void remove_duplicate_lines() {
  char *filename = "registroResidente.txt";
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo %s\n", filename);
    exit(1);
  }

  char lines[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
  int line_count = 0;
  while (fgets(lines[line_count], MAX_LINE_LENGTH, file) != NULL) {
    line_count++;
  }
  fclose(file);

  file = fopen(filename, "w");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo %s\n", filename);
    exit(1);
  }

  for (int i = 0; i < line_count; i++) {
    int is_duplicate = 0;
    for (int j = 0; j < i; j++) {
      if (strcmp(lines[i], lines[j]) == 0) {
        is_duplicate = 1;
        break;
      }
    }
    if (!is_duplicate) {
      fputs(lines[i], file);
    }
  }
  fclose(file);
}

void fichaAvaliativa(char *nome, char *curso) {
  printf("\n--- Ficha Avaliativa ---\n");

  if (strcmp(curso, "Enfermagem") == 0) {
    int assiduidade;
    printf("1. ASSIDUIDADE ( 0 – 3 ): ");
    scanf("%d", &assiduidade);

    int pontualidade;
    printf("2. PONTUALIDADE ( 0 – 3 ): ");
    scanf("%d", &pontualidade);

    int biosseguranca;
    printf("3. BIOSSEGURANÇA/VESTUÁRIO ( 0 – 4 ): ");
    scanf("%d", &biosseguranca);

    float iniciativa;
    printf("4. INICIATIVA ( 0 – 0,5 ): ");
    scanf("%f", &iniciativa);

    int posturaEticoProfissional;
    printf("5. POSTURA ÉTICO-PROFISSIONAL ( 0 – 10 ): ");
    scanf("%d", &posturaEticoProfissional);

    int relacionamentoEquipe;
    printf("6. RELACIONAMENTO EM EQUIPE ( 0 – 5 ): ");
    scanf("%d", &relacionamentoEquipe);

    int espiritoCritico;
    printf("7. ESPÍRITO CRÍTICO ( 0 – 10 ): ");
    scanf("%d", &espiritoCritico);

    int comunicacao;
    printf("8. COMUNICAÇÃO ( 0 – 5 ): ");
    scanf("%d", &comunicacao);

    int planejamentoAtividadesEnfermagem;
    printf("9. PLANEJAMENTO DAS ATIVIDADES DE ENFERMAGEM ( 0 – 15 ): ");
    scanf("%d", &planejamentoAtividadesEnfermagem);

    int dominioProcedimentos;
    printf("10. DOMÍNIO DOS PROCEDIMENTOS ( 0 – 15 ): ");
    scanf("%d", &dominioProcedimentos);

    int evolucaoConsultaEnfermagemRegistroProcedimentos;
    printf(
        "11. EVOLUÇÃO/ CONSULTA DE ENFERMAGEM E REGISTRO DOS PROCEDIMENTOS ( "
        "0 – "
        "15 ): ");
    scanf("%d", &evolucaoConsultaEnfermagemRegistroProcedimentos);

    int lideranca;
    printf("12. LIDERANÇA ( 0 – 10 ): ");
    scanf("%d", &lideranca);

    float notaFinal =
        (assiduidade + pontualidade + biosseguranca + iniciativa +
         posturaEticoProfissional + relacionamentoEquipe + espiritoCritico +
         comunicacao + planejamentoAtividadesEnfermagem + dominioProcedimentos +
         evolucaoConsultaEnfermagemRegistroProcedimentos + lideranca) /
        10.0;

    printf("\nNOTA FINAL = %.1f\n", notaFinal);
  } else if (strcmp(curso, "Multiprofissional") == 0) {
    int assiduidade;
    printf("1. ASSIDUIDADE ( 0 – 3 ): ");
    scanf("%d", &assiduidade);

    int pontualidade;
    printf("2. PONTUALIDADE ( 0 – 3 ): ");
    scanf("%d", &pontualidade);

    int biosseguranca;
    printf("3. BIOSSEGURANÇA/VESTUÁRIO ( 0 – 4 ): ");
    scanf("%d", &biosseguranca);

    float iniciativa;
    printf("4. INICIATIVA ( 0 – 0,5 ): ");
    scanf("%f", &iniciativa);

    int posturaEticoProfissional;
    printf("5. POSTURA ÉTICO-PROFISSIONAL ( 0 – 10 ): ");
    scanf("%d", &posturaEticoProfissional);

    int relacionamentoEquipe;
    printf("6. RELACIONAMENTO EM EQUIPE ( 0 – 5 ): ");
    scanf("%d", &relacionamentoEquipe);

    int espiritoCritico;
    printf("7. ESPÍRITO CRÍTICO ( 0 – 10 ): ");
    scanf("%d", &espiritoCritico);

    int comunicacao;
    printf("8. COMUNICAÇÃO ( 0 – 5 ): ");
    scanf("%d", &comunicacao);

    int planejamentoAtividades;
    printf("9. PLANEJAMENTO DAS ATIVIDADES (0 – 10): ");
    scanf("%d", &planejamentoAtividades);

    int dominioProcedimentos;
    printf("10. DOMÍNIO DOS PROCEDIMENTOS ( 0 – 15): ");
    scanf("%d", &dominioProcedimentos);

    int registroProcedimentos;
    printf("11.REGISTRO DOS PROCEDIMENTOS (0 – 10): ");
    scanf("%d", &registroProcedimentos);

    int atuacaoMultiprofissional;
    printf("12.ATUAÇÃO MULTIPROFISSIONAL (0 – 15): ");
    scanf("%d", &atuacaoMultiprofissional);

    int lideranca;
    printf("13. LIDERANÇA (0 – 5): ");
    scanf("%d", &lideranca);

    float notaFinal =
        (assiduidade + pontualidade + biosseguranca + iniciativa +
         posturaEticoProfissional + relacionamentoEquipe + espiritoCritico +
         comunicacao + planejamentoAtividades + dominioProcedimentos +
         registroProcedimentos + atuacaoMultiprofissional + lideranca) /
        10.0;

    printf("\nNOTA FINAL = %.1f\n", notaFinal);

    printf("\nAPONTAR OBSERVAÇÕES: ");
    char observacoes[1000];
    scanf(" %[^\n]", observacoes);

    FILE *arquivo = fopen("fichaDeAvaliacao.txt", "a");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo fichaDeAvaliacao.txt.\n");
      return;
    }

    fprintf(arquivo,
            "Ficha Avaliativa para %s (%s):\n"
            "1. ASSIDUIDADE: %d\n"
            "2. PONTUALIDADE: %d\n"
            "3. BIOSSEGURANÇA/VESTUÁRIO: %d\n"
            "4. INICIATIVA: %.1f\n"
            "5. POSTURA ÉTICO-PROFISSIONAL: %d\n"
            "6. RELACIONAMENTO EM EQUIPE: %d\n"
            "7. ESPÍRITO CRÍTICO: %d\n"
            "8. COMUNICAÇÃO: %d\n"
            "9. PLANEJAMENTO DAS ATIVIDADES: %d\n"
            "10. DOMÍNIO DOS PROCEDIMENTOS: %d\n"
            "11.REGISTRO DOS PROCEDIMENTOS: %d\n"
            "12.ATUAÇÃO MULTIPROFISSIONAL: %d\n"
            "13. LIDERANÇA: %d\n"
            "NOTA FINAL = %.1f\n"
            "OBSERVAÇÕES: %s\n\n",
            nome, curso, assiduidade, pontualidade, biosseguranca, iniciativa,
            posturaEticoProfissional, relacionamentoEquipe, espiritoCritico,
            comunicacao, planejamentoAtividades, dominioProcedimentos,
            registroProcedimentos, atuacaoMultiprofissional, lideranca,
            notaFinal, observacoes);

    fclose(arquivo);

    printf("Ficha avaliativa salva com sucesso.\n");
  } else if (strcmp(curso, "Nutrição") == 0) {
    printf("As competências estarão no regulamento, no início do aplicativo\n");

    int competencias;
    printf("1. COMPETÊNCIAS (0 - 6): ");
    scanf("%d", &competencias);

    int habilidades;
    printf("2. HABILIDADES (0 - 2): ");
    scanf("%d", &habilidades);

    int atitudes;
    printf("3. ATITUDES (0 - 2): ");
    scanf("%d", &atitudes);

    int notaFinal = competencias + habilidades + atitudes;

    printf("\nNOTA FINAL = %d\n", notaFinal);

    printf("\nAPONTAR OBSERVAÇÕES: ");
    char observacoes[1000];
    scanf(" %[^\n]", observacoes);

    FILE *arquivo = fopen("fichaDeAvaliacao.txt", "a");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo fichaDeAvaliacao.txt.\n");
      return;
    }

    fprintf(arquivo,
            "Ficha Avaliativa para %s (%s):\n"
            "1. COMPETÊNCIAS: %d\n"
            "2. HABILIDADES: %d\n"
            "3. ATITUDES: %d\n"
            "NOTA FINAL = %d\n"
            "OBSERVAÇÕES: %s\n\n",
            nome, curso, competencias, habilidades, atitudes, notaFinal,
            observacoes);

    fclose(arquivo);

    printf("Ficha avaliativa salva com sucesso.\n");
  } else if (strcmp(curso, "Médica") == 0) {
    int assiduidade;
    printf("1. ASSIDUIDADE ( 0 – 5): ");
    scanf("%d", &assiduidade);

    int pontualidade;
    printf("2. PONTUALIDADE ( 0 – 5): ");
    scanf("%d", &pontualidade);

    int iniciativa;
    printf("3. INICIATIVA (0 – 5): ");
    scanf("%d", &iniciativa);

    int posturaEticoProfissional;
    printf("4. POSTURA ÉTICO-PROFISSIONAL (0 – 15): ");
    scanf("%d", &posturaEticoProfissional);

    int relacionamentoEquipe;
    printf("5. RELACIONAMENTO EM EQUIPE ( 0 – 10 ): ");
    scanf("%d", &relacionamentoEquipe);

    int espiritoCritico;
    printf("6. ESPÍRITO CRÍTICO ( 0 – 5 ): ");
    scanf("%d", &espiritoCritico);

    int comunicacao;
    printf("7. COMUNICAÇÃO ( 0 – 5 ): ");
    scanf("%d", &comunicacao);

    int habilidadesCompetenciasEspecificas;
    printf("8. HABILIDADES E COMPETÊNCIAS ESPECÍFICAS (0 - 35): ");
    scanf("%d", &habilidadesCompetenciasEspecificas);

    int participacaoAtividadesTeoricas;
    printf("9. PARTICIPAÇÃO NAS ATIVIDADES TEÓRICAS (0 - 15): ");
    scanf("%d", &participacaoAtividadesTeoricas);

    float notaFinal =
        (assiduidade + pontualidade + iniciativa + posturaEticoProfissional +
         relacionamentoEquipe + espiritoCritico + comunicacao +
         habilidadesCompetenciasEspecificas + participacaoAtividadesTeoricas) /
        10.0;

    printf("\nNOTA FINAL = %.1f\n", notaFinal);

    printf("\nAPONTAR OBSERVAÇÕES: ");
    char observacoes[1000];
    scanf(" %[^\n]", observacoes);

    FILE *arquivo = fopen("fichaDeAvaliacao.txt", "a");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo fichaDeAvaliacao.txt.\n");
      return;
    }

    fprintf(arquivo,
            "Ficha Avaliativa para %s (%s):\n"
            "1. ASSIDUIDADE: %d\n"
            "2. PONTUALIDADE: %d\n"
            "3. INICIATIVA: %d\n"
            "4. POSTURA ÉTICO-PROFISSIONAL: %d\n"
            "5. RELACIONAMENTO EM EQUIPE: %d\n"
            "6. ESPÍRITO CRÍTICO: %d\n"
            "7. COMUNICAÇÃO: %d\n"
            "8. HABILIDADES E COMPETÊNCIAS ESPECÍFICAS: %d\n"
            "9. PARTICIPAÇÃO NAS ATIVIDADES TEÓRICAS: %d\n"
            "NOTA FINAL = %.1f\n"
            "OBSERVAÇÕES: %s\n\n",
            nome, curso, assiduidade, pontualidade, iniciativa,
            posturaEticoProfissional, relacionamentoEquipe, espiritoCritico,
            comunicacao, habilidadesCompetenciasEspecificas,
            participacaoAtividadesTeoricas, notaFinal, observacoes);

    fclose(arquivo);

    printf("Ficha avaliativa salva com sucesso.\n");
  }
}

void imprimirFichaAvaliacao(char *nomeResidente) {
  FILE *arquivo = fopen("fichaDeAvaliacao.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo fichaDeAvaliacao.txt.\n");
    return;
  }

  char linha[1000];
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (strstr(linha, nomeResidente) != NULL) {
      printf("%s", linha);
      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        if (strcmp(linha, "\n") == 0) {
          break;
        }
      }
      break;
    }
  }

  fclose(arquivo);
}

void imprimirFeedback(char *nomeResidente) {
  FILE *arquivo = fopen("feedback.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo feedback.txt.\n");
    return;
  }

  char linha[1000];
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (strstr(linha, nomeResidente) != NULL) {
      printf("%s", linha);
      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        if (strcmp(linha, "\n") == 0) {
          break;
        }
      }
      break;
    }
  }

  fclose(arquivo);
}

void ListaDeResidentesGestor() {
  FILE *arquivo = fopen("residenteDados.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo residenteDados.txt.\n");
    return;
  }

  Residente residentes[MAX_RESIDENTES];
  int numResidentes = 0;

  char linha[100];
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (strstr(linha, "Nome:") ==
        linha) { // Verifica se a linha começa com "Nome:"
      strcpy(residentes[numResidentes].nome, linha + 6); // Ignora "Nome: "
      residentes[numResidentes]
          .nome[strcspn(residentes[numResidentes].nome, "\n")] = '\0';

      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strstr(linha, "Curso:") ==
            linha) { // Verifica se a linha começa com "Curso:"
          strcpy(residentes[numResidentes].curso,
                 linha + 7); // Ignora "Curso: "
          residentes[numResidentes]
              .curso[strcspn(residentes[numResidentes].curso, "\n")] = '\0';
          break;
        }
      }

      numResidentes++;
    }
  }

  fclose(arquivo);

  qsort(residentes, numResidentes, sizeof(Residente), comparaResidente);

  char cursoAnterior[100] = "";
  for (int i = 0; i < numResidentes; i++) {
    if (strcmp(cursoAnterior, residentes[i].curso) != 0) {
      printf("\nResidência %s\n\n", residentes[i].curso);
      strcpy(cursoAnterior, residentes[i].curso);
    }

    printf("%d. Nome: %s\n", i + 1, residentes[i].nome);
  }

  printf("\nDigite o número do residente para ver mais detalhes: ");
  int escolha;
  scanf("%d", &escolha);
  escolha--;

  if (escolha >= 0 && escolha < numResidentes) {
    int opcao;
    do {
      printf("\n--- Avaliação ---\n");
      printf("1. Monitoramento\n");
      printf("2. Sair\n");
      printf("Digite sua opção: ");
      scanf("%d", &opcao);

      switch (opcao) {
      case 1:
        printf("\n--- Monitoramento ---\n");
        printf("Nome: %s\n", residentes[escolha].nome);
        printf("Curso: %s\n", residentes[escolha].curso);
        calendario(residentes[escolha].nome);
        showTotalProgress(residentes[escolha].nome);
        break;
      case 2:
        break;
      default:
        printf("Opção inválida.\n");
        break;
      }
    } while (opcao != 4);
  } else {
    printf("Escolha inválida.\n");
  }
}

void imprimirPreceptores() {
  FILE *arquivo = fopen("preceptorDados.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo preceptorDados.txt.\n");
    return;
  }

  char linha[1000];
  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    if (strstr(linha, "Nome: ") != NULL) {
      printf("%s", linha + strlen("Nome: "));
    }
  }

  fclose(arquivo);
}
