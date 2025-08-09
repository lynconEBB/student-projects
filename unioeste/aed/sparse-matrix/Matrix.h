#ifndef MATRIZESPARSA_MATRIX_H
#define MATRIZESPARSA_MATRIX_H
#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar as informacoes de uma celula da matriz esparsa
typedef struct cell {
    int row, column;
    struct cell* right;
    struct cell* down;
    int value;
} Cell;

// Estrutura que representa uma matriz esparasa
typedef struct {
    int rows, columns; // Ordem da matriz
    Cell* head; // Ponteiro para a celula na linha -1 e coluna -1
} Matrix;

// Enum para uso interno com intuito de identificar a operacao a ser executada
typedef enum {
 SUBTRATION,
 SUM
} Operation;

// Handle para uso interno, criado a partir de uma matriz ja existente com o
// objetivo de armazenar celulas importantes para o processo de insercao
typedef struct {
    Cell* matrixHead; // Celula -1 x -1 da matriz
    Cell* currRowHead; // Celula representando a cabeca da linha atual
    Cell* currColumnHead; // Celula representando a cabeca da coluna atual
    Cell* leftNeighbor; // Ultima celula inserida na linha
    Cell* upNeighbor; // Ultima celula inserida na coluna
} MatrixHandle;

// Cria uma matriz a partir de um arquivo
// Pré-condição: Ponteiro para arquivo aberto e com as informações necessárias para criação da matriz
// Pós-condição: Nova matriz criada a partir do arquivo, caso exista formatação invalida NULL é retornado
Matrix* createFromFile(FILE* file);

// Imprime os valores presentes na matriz formatados em suas devidas posições
// Pré-condição: Ponteiro valido para uma matriz ou nulo
// Pós-condição: Valores formatados da matriz impressos no console
void printMatrix(const Matrix* m);

// Cria a matriz resultante da soma de duas matrizes
// Pré-condição: 2 ponteiros para matrizes válidas
// Pós-condiçao: Matriz resultante da soma criada caso as matrizes contenham a mesma ordem, caso contrario NULL é retornado
Matrix* sumMatrices(const Matrix* m1, const Matrix* m2);

// Cria a matriz resultante da subtracao de duas matrizes
// Pré-condição: 2 ponteiros para matrizes válidas
// Pós-condiçao: Matriz resultante da subtração criada caso as matrizes contenham a mesma ordem, caso contrario NULL é retornado
Matrix* subtractMatrices(const Matrix* m1, const Matrix* m2);

// Cria a matriz resultante da multiplicação de duas matrizes
// Pré-condição: 2 ponteiros para matrizes válidas
// Pós-condiçao: Matriz resultante da multiplicação criada caso as matrizes contenham ordens compatives, caso contrario NULL é retornado
Matrix* multiplyMatrices(const Matrix* m1, const Matrix* m2);

// Cria a matriz transposta da matriz fornecida
// Pré-condição: Ponteiro valido para uma matriz
// Pós-condiçao: Matriz transposta criada
Matrix* transposeOf(const Matrix* m );

// Verifica se a matriz fornecida é simétrica
// Pré-condição: Poteiro valido para uma matriz
// Pós-condição: 1 é retornado caso matriz seja simétrica, caso contrario 0 é retornado
int isSymmetric(const Matrix* m);

// Libera o espaço na memória ocupado pela matriz e todas suas células
// Pré-condição: Ponteiro para o ponteiro de uma matriz valida
// Pós-condição: Espaço ocupado pela matriz e suas celulas liberadas e ponteiro agora aponta para NULL
void freeMatrix(Matrix** m);

#endif
