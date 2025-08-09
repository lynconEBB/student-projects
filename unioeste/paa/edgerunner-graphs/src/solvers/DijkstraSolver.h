#ifndef GRAPHS_DIJKSTRASOLVER_H
#define GRAPHS_DIJKSTRASOLVER_H
#include "Solver.h"
#include <queue>

class DijkstraSolver : public Solver{
    // Fila de prioridade de arestas ordenada em ordem crescente de peso.
    using EdgePriorityQueue = std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>;

public:
    // Resolve o problema do caminho mínimo utilizando o algoritmo de Dijkstra
    // Pré-condição: o grafo deve estar devidamente inicializado.
    // Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
    void solve(Graph graph) override;

    // Verifica se o grafo de entrada é válido para o algoritmo de Dijkstra.
    // Pré-condição: o grafo deve estar devidamente inicializado.
    // Pós-condição: retorna true se o grafo atende às condições e false caso contrário.
    bool validate(Graph graph) override;

private:
    // Calcula a distância mínima e o caminho até cada vértice do grafo a partir de um vértice de origem usando o algoritmo de Dijkstra.
    // Pré-condição: o grafo deve estar devidamente inicializado. A fila de prioridade priorityQueue deve estar vazia,
    //               enquanto os vetores distance e previous devem estar inicializados corretamente.
    // Pós-condição: os vetores distance e previous contêm as informações do caminho mais curto a partir do vértice de origem,
    //               enquanto a fila de prioridade priorityQueue está vazia.
    void minDistance(Graph graph, int32_t origin, std::vector<int32_t>& distance,
                     std::vector<int32_t>& previous, EdgePriorityQueue& priorityQueue);

    // Imprime o resultado da solução do algoritmo de Dijkstra para o grafo de entrada.
    // Pré-condição: o grafo deve estar devidamente inicializado. Os vetores distance e previous devem conter as informações
    //               do caminho mais curto a partir do vértice de origem.
    // Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
    void print(Graph graph, std::vector<int32_t> distance, std::vector<int32_t> previous, int32_t origin);
};

#endif
