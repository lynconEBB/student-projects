#include "App.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Lê uma linha do console criando uma string com tamanho adequado
// Pré-condição: Nenhuma
// Pós-condição: Ponteiro para string dinamicamente aloca retornado com conteudo lido
static char* aux_readLine()
{
    char tmp[100], *str = NULL;
    int n, used = 0;
    while (1) {
        if (!fgets(tmp, sizeof(tmp), stdin))
            return str;

        n = strcspn(tmp,"\n");
        tmp[n] = '\0';

        str = realloc(str, sizeof(char) * (used + n + 1));
        memcpy(str + used,tmp, n + 1 );
        used += n;

        if (n + 1 < sizeof(tmp)) {
            break;
        }
    }
    return str;
}

// Indica a quantidade de arquivos necessários para a opção escolhida
// Pré-condição: nenhuma
// Pós-condição: quantidade de arquivos necessários para a opção retornado
static int aux_opToFileAmount(Option op)
{
    switch(op) {
        case OP_SUM:
        case OP_SUBTRACT:
        case OP_MULTIPLY:
            return 2;
        case OP_SYMMETRIC:
        case OP_EXEC_FILE:
        case OP_TRANSPOSE:
            return 1;
        default:
            return 0;
    }
}

// Indica a quantidade de matrizes necessárias para a opção escolhida
// Pré-condição: nenhuma
// Pós-condição: quantidade de matrizes necessárias para a opção retornado
static int aux_opToMatricesAmount(Option op)
{
    switch(op) {
        case OP_SUM:
        case OP_SUBTRACT:
        case OP_MULTIPLY:
            return 2;
        case OP_SYMMETRIC:
        case OP_TRANSPOSE:
            return 1;
        default:
            return 0;
    }
}

// Imprime as matrizes e mensagens resultantes da operação em questão
// Pré-condição: Buffer de matrizes preenchido corretamente com ponteiros válidos
// Pós-condição: Resultado impresso no console
static void aux_printOptionResult(Option op, Matrix* matrices[])
{
    switch (op) {
        case OP_SUM:
        case OP_MULTIPLY:
        case OP_SUBTRACT:
            printMatrix(matrices[0]);

            (op == OP_SUM) ? printf("+\n") :
            (op == OP_SUBTRACT) ? printf("-\n"): printf("x\n");

            printMatrix(matrices[1]);
            printMatrix(matrices[2]);
            break;
        case OP_TRANSPOSE:
            printMatrix(matrices[0]);
            printf("Transposta igual a:\n");
            printMatrix(matrices[1]);
            break;
        case OP_SYMMETRIC:
            printMatrix(matrices[0]);
            break;
    }
}

// Inicia o loop da aplicação
// Pré-condição: Vetor de ponteiros de matrizes e vetor de ponteiros para arquivos com tamanho maior ou igual ao definido
// Pós-condição: Aplicação iniciada, requisitando informações ao usuário e imprimindo os resultados
void startApp(Matrix* mBuffer[], FILE* fBuffer[])
{
    Option option;

    printTitle();
    do {
        printMenu();
        if (!requestOption(&option))
            continue;
        requestAndLoadFiles(option, fBuffer);

        if (option == OP_EXEC_FILE && !getOptionFromFile(fBuffer[0], &option))
            continue;

        if (!loadMatrices(option, mBuffer, fBuffer))
            continue;
        executeOption(option, mBuffer);

        cleanBuffers(fBuffer, mBuffer);
    } while (option != OP_EXIT);
}

// Requisita ao usuário que insera a opção desejada
// Pré-condição: nenhuma
// Pós-condição: caso opção valida tenha sido inserida 1 é retornada, caso contrario 0 é retornado
int requestOption(Option* op)
{
    if (scanf("%u%*c", op) != 1) {
        fflush(stdin);
        return 0;
    }
    return 1;
}

// Requista uma quantidade de arquivos ao usuario baseada na opção escolhida e adicina estes ao buffer de arquivos
// Pré-condição: Opção válida e vetor ponteiros nulos de arquivos
// Pós-condição: Arquivos requistados inseridos no buffer de arquivos
void requestAndLoadFiles(Option op, FILE* files[])
{
    for (int i = 0; i < aux_opToFileAmount(op); i++){
        printf("Insira o arquivo:");
        while (1) {
            char* fileName = aux_readLine();
            files[i] = fopen(fileName,"r");
            free(fileName);

            if (files[i] == NULL)
                printf("Arquivo nao encontrado, insira outro arquivo:");
            else
                break;
        }
    }
}

// Cria uma quantidade de matrizes e adiciona ao buffer matrizes com base na opção e nos arquivos carregados
// Pré-condição: Opção válida, buffer de arquivos abertos e vetor de ponteiros nulos de matrizes
// Pós-condição: Matrizes criadas e adicionadas ao buffer de matrizes
int loadMatrices(Option op,Matrix* matrices[], FILE* files[])
{
    int currFile = 0;
    for(int i = 0; i < aux_opToMatricesAmount(op); i++) {
        matrices[i] = createFromFile(files[currFile]);
        if (!matrices[i]) {
            printf("Erro na leitura do arquivo\n");
            return 0;
        } else
            printf("Matriz carregada na memoria!\n");
        if (files[currFile+1])
            currFile++;
    }
    return 1;
}

// Executa a opçao desejada adicionando a matriz resultante ao buffer de matrizes caso necessário
// Pré-condição: opção valida e vertor de ponteiro para matrizes válido
// Pós-condição: Resultado adicioanda ao buffer de matrizes e exibido no console
void executeOption(Option op, Matrix* matrices[])
{
    switch (op) {
        case OP_SUM:
        case OP_MULTIPLY:
        case OP_SUBTRACT:
            matrices[2] = ((op == OP_SUBTRACT) ? subtractMatrices(matrices[0], matrices[1]):
                           (op == OP_SUM) ? sumMatrices(matrices[0], matrices[1]):
                           multiplyMatrices(matrices[0],matrices[1]));
            if (matrices[2] == NULL)
                printf("Matrizes com ordens diferentes!\n");
            aux_printOptionResult(op, matrices);
            break;
        case OP_TRANSPOSE:
            matrices[1] = transposeOf(matrices[0]);
            aux_printOptionResult(op, matrices);
            break;
        case OP_SYMMETRIC:
            aux_printOptionResult(op, matrices);
            if (isSymmetric(matrices[0]))
                printf("simetrica: SIM\n");
            else
                printf("simetrica: NAO\n");
            break;
        case OP_EXIT:
            printf("Saindo do progama!\n");
            break;
    }
}

// Limpa os buffers de arquivos e matrizes e transformando os ponteiros em ponteiros nulos
// Pré-condição: nenhuma
// Pós-condição: arquivos fechados e memorria ocupada pelas matrizes liberada, ponteiros agora são nulos
void cleanBuffers(FILE* fBuffer[], Matrix* mBuffer[])
{
    for (int i = 0; i < MIN_F_BUFFER; i++) {
        fclose(fBuffer[i]);
        fBuffer[i] = NULL;
    }
    for (int i = 0; i < MIN_M_BUFFER; i++) {
        freeMatrix(&mBuffer[i]);
    }
}

// Modifica a opção para a opção requerida pelo arquivo de execução
// Pré-condição: ponteiro para arquivo aberto e opção escolhida seja OP_EXEC_FILE
// Pós-condição: Caso seja possivel ler a opção no arquivo 1 é retornado, caso contrario 0 é retornado
int getOptionFromFile(FILE* file, Option* op)
{
    char buffer[30];
    fgets(buffer, sizeof(buffer), file);
    buffer[strcspn(buffer,"\n")] = '\0';
    if (!strcmp(buffer,"soma"))
        *op = OP_SUM;
    else if (!strcmp(buffer,"subtracao"))
        *op = OP_SUBTRACT;
    else if (!strcmp(buffer,"multiplicacao"))
        *op = OP_MULTIPLY;
    else if (!strcmp(buffer,"transposta"))
        *op = OP_TRANSPOSE;
    else if (!strcmp(buffer,"simetrica"))
        *op = OP_SYMMETRIC;
    else {
        printf("Nao foi possivel encontrar cabecalho com a opercao\n");
        return 0;
    }
    return 1;
}

// Imprime o menu com as opções disponíveis
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void printMenu()
{
    printf("\n1 - Somar 2 matrizes\n");
    printf("2 - Subtrair 2 matrizes\n");
    printf("3 - Multiplicar 2 matrizes\n");
    printf("4 - Gerar matriz transposta\n");
    printf("5 - Verificar se uma matriz e simetrica\n");
    printf("6 - Executar um arquivo de operacao\n");
    printf("7 - Sair\n\n");
    printf("O que deseja fazer?");
}

// Imprime o título da aplicação em ascii art
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void printTitle()
{
    printf("==============================================\n"
            "  __  __       _______ _____  _______   __\n"
           " |  \\/  |   /\\|__   __|  __ \\|_   _\\ \\ / /\n"
           " | \\  / |  /  \\  | |  | |__) | | |  \\ V /\n"
           " | |\\/| | / /\\ \\ | |  |  _  /  | |   > <\n"
           " | |  | |/ ____ \\| |  | | \\ \\ _| |_ / . \\\n"
           " |_|  |_/_/    \\_\\_|  |_|  \\_\\_____/_/ \\_\\\n"
           "==============================================\n");
}