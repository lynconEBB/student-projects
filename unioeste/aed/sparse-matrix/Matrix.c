#include "Matrix.h"
#include <string.h>


// Estrai o numero de linhas e colunas da matriz e insere na matriz fornecida
// Pré-condição: Ponteiro para arquivo aberto e ponteiro valido para matriz
// Pós-condição: Retorna 1 caso leitura e inserção tenham sido concluidas, caso contrário 0 é retornado
static int aux_setDimensionsFromFile(FILE* file, Matrix* m ) {
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);

    char* search = strchr(buffer, 'x');
    if (search)
        *search = 'X';

    if (sscanf(buffer, "%dX%d", &m->rows, &m->columns) != 2)
        return 0;
    return 1;
}

// Insere celulas cabeças das linhas e colunas com base no numero de linhas e colunas da matriz
// Pré-condição: Ponteiro valido para matriz com numero de linhas e colunas
// Pós-condição: Celulas cabeças criadas com informações corretas inseridas
static void aux_setHeads(Matrix* m)
{
    m->head = malloc(sizeof(Cell));
    m->head->column = -1;
    m->head->row = -1;
    m->head->down = m->head;
    m->head->right = m->head;

    Cell* prev = m->head;
    for (int i = 1; i <= m->columns; i++) {
        Cell* curr = malloc(sizeof(Cell));
        curr->row = -1;
        curr->column = i;
        curr->down = curr;
        prev->right = curr;
        prev = curr;
    }
    prev->right = m->head;

    prev = m->head;
    for (int i = 1; i <= m->rows; i++) {
        Cell* curr = malloc(sizeof(Cell));
        curr->row = i;
        curr->column = -1;
        curr->right = curr;
        prev->down = curr;
        prev = curr;
    }
    prev->down = m->head;
}

// Adiciona celula na linha e coluna desejada
// Pré-condição: Handle valido criado a partir de uma matriz, numero da coluna e linha maiores que os das celulas presentes no handle
// Pós-condição: Nova celula criada e adicionada na matriz criadora do handle
static void aux_appendCell(int row, int column, int value, MatrixHandle* s)
{
    Cell* curr = malloc(sizeof(Cell));
    curr->row = row;
    curr->column = column;
    curr->value = value;

    if (s->currRowHead->row != curr->row) {
        s->currColumnHead = s->matrixHead;

        while (s->currRowHead->row != curr->row) {
            s->currRowHead = s->currRowHead->down;
        }
        s->leftNeighbor = s->currRowHead;
        while (s->leftNeighbor->right != s->currRowHead) {
            s->leftNeighbor = s->leftNeighbor->right;
        }
    }

    s->leftNeighbor->right = curr;
    curr->right = s->currRowHead;
    s->leftNeighbor = curr;

    while (s->currColumnHead->column != curr->column) {
        s->currColumnHead = s->currColumnHead->right;
    }
    s->upNeighbor = s->currColumnHead;
    while (s->upNeighbor->down != s->currColumnHead) {
        s->upNeighbor = s->upNeighbor->down;
    }

    s->upNeighbor->down = curr;
    curr->down = s->currColumnHead;
}

// Cria handle a partir de uma matriz para inserção de celulas em interação
// Pré-condição: ponteiro pra matriz com numero de linhas e colunas prontos e cabeças de todas linhas e colunas
// Pós-condição: handle criado a partir da matriz fornecida
static MatrixHandle* aux_createHandle(Matrix* m)
{
    MatrixHandle* s = malloc(sizeof(MatrixHandle));
    s->matrixHead = m->head;
    s->currRowHead = m->head;
    s->currColumnHead = m->head;
    s->leftNeighbor = NULL;
    s->upNeighbor = NULL;
    return s;
}

// Verifica se uma célula é cabeça de uma linha
// Pré-condição: ponteiro válido para célula
// Pós-condição: 1 é retornado caso a célula seja cabeça da linha, caso contrario 0 é retornado
static int aux_isRowHead(Cell* c)
{
    return (c->column == -1);
}

// Verifica se uma célula é cabeça de uma coluna
// Pré-condição: ponteiro válido para célula
// Pós-condição: 1 é retornado caso a célula seja cabeça da coluna, caso contrario 0 é retornado
static int aux_isColumnHead(Cell* c)
{
    return (c->row == -1);
}

// Executa operacao de soma ou subtracao e insere no final da matriz
// Pré-condição: Celulas atuais da iteracao, uma operacao a ser executada e um handle valido
// Pós-condição: Nova celulas criada com valor do resultado da operação e adicionada a matriz geradora do handle
static void aux_operateAndAppend(Cell** cell1 , Cell** cell2, Operation op, MatrixHandle* s) {
    if ((*cell1)->column == (*cell2)->column) {
        int resul = (op == SUBTRATION) ?
                    (*cell1)->value - (*cell2)->value :
                    (*cell1)->value + (*cell2)->value;
        if (resul)
            aux_appendCell((*cell1)->row, (*cell1)->column, resul, s);
        (*cell1) = (*cell1)->right;
        (*cell2) = (*cell2)->right;
    }
    else if (aux_isRowHead(*cell2) || ((*cell1)->column < (*cell2)->column && !aux_isRowHead(*cell1))) {
        aux_appendCell((*cell1)->row, (*cell1)->column, (*cell1)->value, s);
        (*cell1) = (*cell1)->right;
    }
    else  {
        int value = op == SUBTRATION ? -(*cell2)->value : (*cell2)->value;
        aux_appendCell((*cell2)->row, (*cell2)->column, value, s);
        (*cell2) = (*cell2)->right;
    }
}

// Cria a matriz resultante da soma ou subtração de duas matrizes
// Pré-condição: 2 ponteiros para matrizes válidas e a operação a ser executada nessas matrizes
// Pós-condiçao: Matriz resultante da soma ou subtração criada caso as matrizes contenham a mesma ordem, caso contrario NULL é retornado
static Matrix* aux_execBasicOperation(Operation op, const Matrix* m1, const Matrix* m2 )
{
    if (m1->rows != m2->rows || m1->columns != m2->columns) {
        return NULL;
    }

    Matrix* newMatrix = malloc(sizeof(Matrix));
    newMatrix->rows = m1->rows;
    newMatrix->columns = m1->columns;
    aux_setHeads(newMatrix);
    MatrixHandle* handle = aux_createHandle(newMatrix);

    Cell *currRow1 = m1->head->down, *currRow2 = m2->head->down;

    while (currRow1 != m1->head && currRow2 != m2->head) {
        Cell *currCell1 = currRow1->right, *currCell2 = currRow2->right;

        while (currCell1 != currRow1 || currCell2 != currRow2) {
            aux_operateAndAppend(&currCell1, &currCell2, op, handle);
        }
        currRow1 = currRow1->down;
        currRow2 = currRow2->down;
    }
    free(handle);
    return newMatrix;
}

// Cria uma matriz a partir de um arquivo
// Pré-condição: Ponteiro para arquivo aberto e com as informações necessárias para criação da matriz
// Pós-condição: Nova matriz criada a partir do arquivo, caso exista formatação invalida NULL é retornado
Matrix *createFromFile(FILE* file)
{
    char buffer[100];

    Matrix* m = malloc(sizeof(Matrix));
    if (!aux_setDimensionsFromFile(file, m)) {
       free(m);
        return NULL;
    }
    aux_setHeads(m);
    MatrixHandle* handle = aux_createHandle(m);

    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer,"\n")] = '\0';
        if (!strcmp(buffer,"fim"))
            break;

        int row, col, value;
        if (sscanf(buffer, "%d,%d,%d", &row, &col, &value) != 3) {
            freeMatrix(&m);
            return NULL;
        }

        aux_appendCell(row, col, value, handle);
    }

    free(handle);
    return m;
}

// Imprime os valores presentes na matriz formatados em suas devidas posições
// Pré-condição: Ponteiro valido para uma matriz ou nulo
// Pós-condição: Valores formatados da matriz impressos no console
void printMatrix(const Matrix* m)
{
    if (m == NULL || m->head->right == m->head) {
        printf("[ ]\n");
        return;
    }

    Cell* headLine = m->head->down;
    printf("\n");
    for (int i = 1; i <= m->rows; i++) {
        Cell* curr = headLine->right;
        printf("[ ");
        for (int j = 1; j <= m->columns; j++) {
            if (curr->row == i && curr->column == j) {
                printf("%4d%4s", curr->value, "");
                curr = curr->right;
            } else {
                printf("   0    ");
            }
        }
        printf("]\n");
        headLine = headLine->down;
    }
    printf("\n");
}

// Cria a matriz resultante da soma de duas matrizes
// Pré-condição: 2 ponteiros para matrizes válidas
// Pós-condiçao: Matriz resultante da soma criada caso as matrizes contenham a mesma ordem, caso contrario NULL é retornado
Matrix* sumMatrices(const Matrix* m1, const Matrix* m2) {
    return aux_execBasicOperation(SUM, m1, m2);
}

// Cria a matriz resultante da subtracao de duas matrizes
// Pré-condição: 2 ponteiros para matrizes válidas
// Pós-condiçao: Matriz resultante da subtração criada caso as matrizes contenham a mesma ordem, caso contrario NULL é retornado
Matrix* subtractMatrices(const Matrix* m1, const Matrix* m2) {
    return aux_execBasicOperation(SUBTRATION, m1, m2);
}

// Cria a matriz resultante da multiplicação de duas matrizes
// Pré-condição: 2 ponteiros para matrizes válidas
// Pós-condiçao: Matriz resultante da multiplicação criada caso as matrizes contenham ordens compatives, caso contrario NULL é retornado
Matrix *multiplyMatrices(const Matrix *m1, const Matrix *m2) {
    if (m1->columns != m2->rows)
        return NULL;

    Matrix* newMatrix = malloc(sizeof(Matrix));
    newMatrix->rows = m1->rows;
    newMatrix->columns = m2->columns;
    aux_setHeads(newMatrix);
    MatrixHandle* handle = aux_createHandle(newMatrix);

    for (Cell *currRow = m1->head->down; currRow != m1->head; currRow = currRow->down ) {
        for (Cell *currColumn = m2->head->right; currColumn != m2->head; currColumn = currColumn->right ){

            Cell* cell1 = currRow->right;
            Cell* cell2 = currColumn->down;
            int sum = 0;

            while (cell1 != currRow && cell2 != currColumn) {
                if (cell1->column == cell2->row) {
                    sum += cell1->value * cell2->value;
                    cell1 = cell1->right;
                    cell2 = cell2->down;
                }
                else if (cell1->column > cell2->row) {
                    cell2 = cell2->down;
                } else if (cell1->column < cell2->row) {
                    cell1 = cell1->right;
                }
            }
            if (sum)
                aux_appendCell(currRow->row, currColumn->column, sum, handle);
        }
    }
    free(handle);
    return newMatrix;
}

// Cria a matriz transposta da matriz fornecida
// Pré-condição: Ponteiro valido para uma matriz
// Pós-condiçao: Matriz transposta criada
Matrix *transposeOf(const Matrix *m)
{
    Matrix* newMatrix = malloc(sizeof(Matrix));
    newMatrix->rows = m->columns;
    newMatrix->columns = m->rows;
    aux_setHeads(newMatrix);
    MatrixHandle* handle = aux_createHandle(newMatrix);

    for (Cell* currRow = m->head->down; currRow != m->head; currRow = currRow->down) {
        for (Cell* cell = currRow->right; cell != currRow; cell = cell->right) {
            aux_appendCell(cell->column, cell->row, cell->value, handle);
        }
    }
    free(handle);
    return newMatrix;
}

// Verifica se a matriz fornecida é simétrica
// Pré-condição: Poteiro valido para uma matriz
// Pós-condição: 1 é retornado caso matriz seja simétrica, caso contrario 0 é retornado
int isSymmetric(const Matrix *m) {
    if (m->rows != m->columns)
        return 0;

    Cell* currRow = m->head->down;
    Cell* currColumn = m->head->right;

    while (currRow != m->head && currColumn != m->head ){
        Cell* cellRow = currRow->right;
        Cell* cellColumn = currColumn->down;

        while (cellRow != currRow || cellColumn != currColumn){
            if (aux_isRowHead(cellRow) || aux_isColumnHead(cellColumn) || cellColumn->value != cellRow->value)
                return 0;
            cellRow = cellRow->right;
            cellColumn = cellColumn->down;
        }
        currColumn = currColumn->right;
        currRow = currRow->down;
    }
    return 1;
}

// Libera o espaço na memória ocupado pela matriz e todas suas células
// Pré-condição: Ponteiro para o ponteiro de uma matriz valida
// Pós-condição: Espaço ocupado pela matriz e suas celulas liberadas e ponteiro agora aponta para NULL
void freeMatrix(Matrix** m) {
    if (*m == NULL)
        return;

    Cell* currRow = (*m)->head;
    for (int i = 0; i < (*m)->rows; i++) {
        Cell* currCell = currRow->right;
        while (currCell != currRow){
            Cell* aux = currCell->right;
            free(currCell);
            currCell = aux;
        }

        Cell* aux = currRow->down;
        free(currRow);
        currRow = aux;
    }
    free(*m);
    *m = NULL;
}