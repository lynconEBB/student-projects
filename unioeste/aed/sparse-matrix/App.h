#ifndef MATRIZESPARSA_APP_H
#define MATRIZESPARSA_APP_H
#include <stdio.h>
#include "Matrix.h"

#define MIN_M_BUFFER 3 // Numero mínimo de ponteiros disponiveis para o bufffer de matrizes
#define MIN_F_BUFFER 2// Numero mínimo de ponteiros disponiveis para o buffer de arquivos

// Enum contendo as opções possiveis de serem realizadas pela aplicação
typedef enum{
    OP_SUM = 1,
    OP_SUBTRACT = 2,
    OP_MULTIPLY = 3,
    OP_TRANSPOSE = 4,
    OP_SYMMETRIC = 5,
    OP_EXEC_FILE = 6,
    OP_EXIT = 7
} Option;

// Inicia o loop da aplicação
// Pré-condição: Vetor de ponteiros nulos de matrizes e vetor de ponteiros nulos para arquivos com tamanho maior ou igual ao definido
// Pós-condição: Aplicação iniciada, requisitando informações ao usuário e imprimindo os resultados
void startApp(Matrix* mBuffer[], FILE* fBuffer[]);

// Requisita ao usuário que insera a opção desejada
// Pré-condição: nenhuma
// Pós-condição: caso opção valida tenha sido inserida 1 é retornada, caso contrario 0 é retornado
int requestOption(Option* op);

// Requista uma quantidade de arquivos ao usuario baseada na opção escolhida e adicina estes ao buffer de arquivos
// Pré-condição: Opção válida e vetor ponteiros nulos de arquivos
// Pós-condição: Arquivos requistados inseridos no buffer de arquivos
void requestAndLoadFiles(Option op, FILE* files[]);

// Cria uma quantidade de matrizes e adiciona ao buffer com base na opção e nos arquivos carregados
// Pré-condição: Opção válida, buffer de arquivos abertos e vetor de ponteiros nulos de matrizes
// Pós-condição: Matrizes criadas e adicionadas ao buffer de matrizes
int loadMatrices(Option op,Matrix* matrices[], FILE* files[]);

// Executa a opçao desejada adicionando a matriz resultante ao buffer de matrizes caso necessário
// Pré-condição: opção valida e vertor de ponteiro para matrizes válido
// Pós-condição: Resultado adicioanda ao buffer de matrizes e exibido no console
void executeOption(Option op, Matrix* matrices[]);

// Modifica a opção para a opção requerida pelo arquivo de execução
// Pré-condição: ponteiro para arquivo aberto e opção escolhida seja OP_EXEC_FILE
// Pós-condição: Caso seja possivel ler a opção no arquivo 1 é retornado, caso contrario 0 é retornado
int getOptionFromFile(FILE* file, Option* op);

// Limpa os buffers de arquivos e matrizes e transformando os ponteiros em ponteiros nulos
// Pré-condição: nenhuma
// Pós-condição: arquivos fechados e memorria ocupada pelas matrizes liberada, ponteiros agora são nulos
void cleanBuffers(FILE* fBuffer[], Matrix* mBuffer[]);

// Imprime o menu com as opções disponíveis
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void printMenu();

// Imprime o título da aplicação em ascii art
// Pré-condição: nenhuma
// Pós-condição: nenhuma
void printTitle();

#endif