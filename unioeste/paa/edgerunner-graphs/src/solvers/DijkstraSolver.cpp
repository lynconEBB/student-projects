#include "DijkstraSolver.h"
#include <iostream>
#include <limits>

// Resolve o problema do caminho mínimo utilizando o algoritmo de Dijkstra
// Pré-condição: o grafo deve estar devidamente inicializado.
// Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
void DijkstraSolver::solve(Graph graph) {
    std::cout << "Insira a origem: ";
    int32_t origin;
    std::cin >> origin;

    std::vector<int32_t> distance(graph.adjList.size(), std::numeric_limits<int32_t>::max());
    std::vector<int32_t> previous(graph.adjList.size(), -1);

    EdgePriorityQueue priorityQueue;

    minDistance(graph, origin, distance, previous, priorityQueue);

    print(graph, distance, previous, origin);
}

// Verifica se o grafo de entrada é válido para o algoritmo de Dijkstra.
// Pré-condição: o grafo deve estar devidamente inicializado.
// Pós-condição: retorna true se o grafo atende às condições e false caso contrário.
bool DijkstraSolver::validate(Graph graph){
    for (int32_t i = 0; i < graph.adjList.size(); i++) {
        for (Edge edge : graph.adjList[i] ) {
            if(edge.weight < 0) {
                std::cout << "Nao e possivel aplicar o algoritmo de Dijkstra - grafo possui arestas com peso negativo!!\n";
                return false;
            }
        }
    }
    return true;
}

// Calcula a distância mínima e o caminho até cada vértice do grafo a partir de um vértice de origem usando o algoritmo de Dijkstra.
// Pré-condição: o grafo deve estar devidamente inicializado. A fila de prioridade priorityQueue deve estar vazia,
//               enquanto os vetores distance e previous devem estar inicializados corretamente.
// Pós-condição: os vetores distance e previous contêm as informações do caminho mais curto a partir do vértice de origem,
//               enquanto a fila de prioridade priorityQueue está vazia.
void DijkstraSolver::minDistance(Graph graph, int32_t origin, std::vector<int32_t>& distance,
                                 std::vector<int32_t>& previous, EdgePriorityQueue& priorityQueue){
    distance[origin] = 0;
    priorityQueue.emplace(origin, 0);

    while (!priorityQueue.empty()) {
        int32_t u = priorityQueue.top().dest;
        priorityQueue.pop();
        for (Edge &edge: graph.adjList[u]) {
            if (distance[edge.dest] > distance[u] + edge.weight) {
                distance[edge.dest] = distance[u] + edge.weight;
                previous[edge.dest] = u;
                priorityQueue.push(Edge(edge.dest, distance[edge.dest]));
            }
        }
    }


}

// Imprime o resultado da solução do algoritmo de Dijkstra para o grafo de entrada.
// Pré-condição: o grafo deve estar devidamente inicializado. Os vetores distance e previous devem conter as informações
//               do caminho mais curto a partir do vértice de origem.
// Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
void DijkstraSolver::print(Graph graph, std::vector<int32_t> distance, std::vector<int32_t> previous, int32_t origin){
    std::cout << "origem: " << origin << std::endl;
    for (int32_t i = 0; i < graph.adjList.size(); i++) {
        std::cout << "destino: " << i << " distância: ";
        if (distance[i] == std::numeric_limits<int32_t>::max()) {
            std::cout << "--" << " caminho: --" << std::endl;
        } else {
            std::cout << distance[i] << " caminho: ";
            std::vector<int32_t> path;
            int32_t j = i;
            while (j != -1) {
                path.push_back(j);
                j = previous[j];
            }
            for (int32_t k = path.size() - 1; k >= 0; k--) {
                std::cout << path[k];
                if (k != 0) {
                    std::cout << " - ";
                }
            }
            std::cout << std::endl;
        }
    }
}
