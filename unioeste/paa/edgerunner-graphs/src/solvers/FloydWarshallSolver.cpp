#include "FloydWarshallSolver.h"
#include <iostream>
#include <limits>
#include <iomanip>

// Resolve o problema do caminho mínimo utilizando o algoritmo de Floid-Warshall.
// Pré-condição: o grafo deve estar devidamente inicializado.
// Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
void FloydWarshallSolver::solve(Graph graph) {
    Matrix distance(graph.adjList.size(), std::vector<int32_t>(graph.adjList.size(), std::numeric_limits<int32_t>::max()));
    Matrix next(graph.adjList.size(), std::vector<int32_t>(graph.adjList.size(), -1));

    initializeMatrix(graph, distance, next);

    minDistance(graph.adjList.size(), distance, next);

    if(hasNegativeCycle(distance)) return;

    printMatrix(graph.adjList.size(), distance);
    printPath(graph.adjList.size(), next);
}

// Verifica se o grafo de entrada é válido para o algoritmo de Floid-Warshall.
// Pré-condição: o grafo deve estar devidamente inicializado.
// Pós-condição: retorna true se o grafo atende às condições e false caso contrário.
bool FloydWarshallSolver::validate(Graph graph){
    return true;
}

// Inicializa as matrizes de distância e próximo.
// Pré-condição: o grafo deve estar devidamente inicializado e as matrizes de distâncias e próximo declaradas.
// Pós-condição: matrizes preenchidas com valores padrão.
void FloydWarshallSolver::initializeMatrix(Graph graph, Matrix& distance, Matrix& next){
    for (int32_t i = 0; i < graph.adjList.size(); i++) {
        for (Edge edge : graph.adjList[i]) {
            distance[i][edge.dest] = edge.weight;
            next[i][edge.dest] = edge.dest;
        }
        distance[i][i] = 0;
        next[i][i] = i;
    }
}

// Calcula a menor distância entre cada par de vértices usando o algoritmo de Floyd-Warshall.
// Pré-condição: quantidade de vertices no grafo, matrizes de distância e próximo inicializadas corretamente.
// Pós-condição: matriz de distância e próximo atualizada com as menores distâncias entre cada par de vértices.
void FloydWarshallSolver::minDistance(int32_t size, Matrix& distance, Matrix& next){
    for (int32_t k = 0; k < size; k++) {
        for (int32_t i = 0; i < size; i++) {
            for (int32_t j = 0; j < size; j++) {
                if (distance[i][k] != std::numeric_limits<int32_t>::max() && distance[k][j] != std::numeric_limits<int32_t>::max()) {
                    if (distance[i][j] > distance[i][k] + distance[k][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
}

// Verifica se há ciclo negativo no grafo a partir da matriz de distância calculada.
// Pré-condição: matriz de distância calculada corretamente.
// Pós-condição: retorna verdadeiro se houver ciclo negativo, falso caso contrário.
bool FloydWarshallSolver::hasNegativeCycle(Matrix distance){
    for (int32_t i = 0; i < distance.size(); i++) {
        if (distance[i][i] < 0) {
            std::cout << "Grafo possui ciclo de peso negativo" << std::endl;
            return true;
        }
    }
    return false;
}

// Imprime a matriz de distância calculada.
// Pré-condição: quantidade de vertices no grafo, matriz de distância calculada corretamente.
// Pós-condição: a matriz de distância é impressa na tela.
void FloydWarshallSolver::printMatrix(int32_t size, Matrix distance){
    std::cout << std::endl << "     ";
    for (int32_t i = 0; i < size; i++) {
        std::cout << std::setw(4) << i << " ";
    }

    std::cout << std::endl;
    for (int32_t i = 0; i < size; i++) {
        std::cout << std::setw(4) << i << " ";
        for (int32_t j = 0; j < size; j++) {
            if (distance[i][j] == std::numeric_limits<int32_t>::max()) {
                std::cout << "  -- ";
            } else {
                std::cout << std::setw(4) << distance[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Imprime o caminho mínimo entre cada par de vértices.
// Pré-condição: quantidade de vertices no grafo, matriz de próximo calculada corretamente.
// Pós-condição: o caminho mínimo entre cada par de vértices é impressa na tela.
void FloydWarshallSolver::printPath(int32_t size, Matrix next){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << "caminho de " << i << " para " << j << ": ";
            if (i == j) {
                std::cout << i;
            } else if (next[i][j] == -1) {
                std::cout << "---";
            } else {
                std::cout << i << " - ";
                int k = next[i][j];
                while (k != j) {
                    std::cout << k << " - ";
                    k = next[k][j];
                }
                std::cout << j;
            }
            std::cout << std::endl;
        }
    }
}