#include "BellmanFordSolver.h"
#include <iostream>
#include <limits>

// Resolve o problema do caminho mínimo utilizando o algoritmo de Bellman-Ford
// Pré-condição: o grafo deve estar devidamente inicializado.
// Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
void BellmanFordSolver::solve(Graph graph) {
    std::cout << "Insira a origem: ";
    int32_t origin;
    std::cin >> origin;

    std::vector<int32_t> distance(graph.adjList.size(), std::numeric_limits<int32_t>::max());
    std::vector<int32_t> previous(graph.adjList.size(), -1);

    minDistance(graph, origin, distance, previous);

    if(hasNegativeCycle(graph, distance)) return;

    print(graph, origin, distance, previous);
}

// Verifica se o grafo de entrada é válido para o algoritmo de Bellman-Ford.
// Pré-condição: o grafo deve estar devidamente inicializado.
// Pós-condição: retorna true se o grafo atende às condições e false caso contrário.
bool BellmanFordSolver::validate(Graph graph){
    if(!graph.isOriented)  {
        std::cout << "Nao e possivel aplicar o algoritmo de Bellman-Ford - grafo nao e orientado!!\n";
        return false;
    }
    return true;
}

// Calcula a distância mínima e o caminho até cada vértice do grafo a partir de um vértice de origem usando o algoritmo de Bellman-Ford.
// Pré-condição: o grafo deve estar devidamente inicializado e os vetores de distâncias e predecessores devem estar inicializados.
// Pós-condição: atualiza os vetores de distâncias e predecessores com as informações do caminho mais curto.
void BellmanFordSolver::minDistance(Graph graph, int32_t origin, std::vector<int32_t>& distance, std::vector<int32_t>& previous) {
    distance[origin] = 0;

    for (int32_t i = 1; i < graph.adjList.size(); ++i) {
        for (int32_t u = 0; u < graph.adjList.size(); ++u) {
            for (Edge& edge : graph.adjList[u]) {
                int32_t v = edge.dest;
                int32_t w = edge.weight;
                if (distance[u] != std::numeric_limits<int32_t>::max() && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    previous[v] = u;
                }
            }
        }
    }
}

// Verifica se o grafo contém ciclos negativos.
// Pré-condição: o grafo deve estar inicializado e o vetores de distâncias com os valores de menor caminho.
// Pós-condição: a função retorna verdadeiro se o grafo contiver ciclos negativos e falso caso contrário.
bool BellmanFordSolver::hasNegativeCycle(Graph graph, std::vector<int32_t>& distance){
    for (int32_t u = 0; u < graph.adjList.size(); ++u) {
        for (Edge& edge : graph.adjList[u]) {
            int32_t v = edge.dest;
            int32_t w = edge.weight;
            if (distance[u] != std::numeric_limits<int32_t>::max() && distance[u] + w < distance[v]) {
                std::cout << "Grafo possui ciclo de peso negativo" << std::endl;
                return true;
            }
        }
    }
    return false;
}


// Imprime o resultado da solução do algoritmo de Dijkstra para o grafo de entrada.
// Pré-condição: o grafo deve estar devidamente inicializado. Os vetores distance e previous devem conter as informações
//               do caminho mais curto a partir do vértice de origem.
// Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
void BellmanFordSolver::print(Graph graph, int32_t origin, std::vector<int32_t> distance, std::vector<int32_t> previous){
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