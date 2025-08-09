#ifndef GRAPHS_BELLMANFORDSOLVER_H
#define GRAPHS_BELLMANFORDSOLVER_H
#include "Solver.h"

class BellmanFordSolver : public Solver{
public:
    // Resolve o problema do caminho mínimo utilizando o algoritmo de Bellman-Ford
    // Pré-condição: o grafo deve estar devidamente inicializado.
    // Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
    void solve(Graph graph) override;

    // Verifica se o grafo de entrada é válido para o algoritmo de Bellman-Ford.
    // Pré-condição: o grafo deve estar devidamente inicializado.
    // Pós-condição: retorna true se o grafo atende às condições e false caso contrário.
    bool validate(Graph graph) override;

private:
    // Calcula a distância mínima e o caminho até cada vértice do grafo a partir de um vértice de origem usando o algoritmo de Bellman-Ford.
    // Pré-condição: o grafo deve estar devidamente inicializado e os vetores de distâncias e predecessores devem estar inicializados.
    // Pós-condição: atualiza os vetores de distâncias e predecessores com as informações do caminho mais curto.
    void minDistance(Graph graph, int32_t origin, std::vector<int32_t>& distance, std::vector<int32_t>& previous);

    // Verifica se o grafo contém ciclos negativos.
    // Pré-condição: o grafo deve estar inicializado e o vetores de distâncias com os valores de menor caminho.
    // Pós-condição: a função retorna verdadeiro se o grafo contiver ciclos negativos e falso caso contrário.
    bool hasNegativeCycle(Graph graph, std::vector<int32_t>& distance);

    // Imprime o resultado da solução do algoritmo de Dijkstra para o grafo de entrada.
    // Pré-condição: o grafo deve estar devidamente inicializado. Os vetores distance e previous devem conter as informações
    //               do caminho mais curto a partir do vértice de origem.
    // Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
    void print(Graph graph, int32_t origin, std::vector<int32_t> distance, std::vector<int32_t> previous);

};


#endif
