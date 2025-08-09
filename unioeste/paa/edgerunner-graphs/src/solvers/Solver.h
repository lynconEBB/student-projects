#ifndef GRAPHS_SOLVER_H
#define GRAPHS_SOLVER_H
#include "../graph/Graph.h"

class Solver {
public:
    // Função que será implementada por cada solver com o algoritmo específico.
    // Pré-requisito: um grafo devidamente inicializado.
    // Pós-requisito: imprime na tela o resultado.
    virtual void solve(Graph graph) = 0;

    // Função que será implementada por cada solver para validar se é possível executar o algoritmo.
    // Pré-requisito: um grafo devidamente inicializado.
    // Pós-requisito: retorna verdadeiro ou falso se puder executar o algoritmo.
    virtual bool validate(Graph graph) = 0;
};

#endif