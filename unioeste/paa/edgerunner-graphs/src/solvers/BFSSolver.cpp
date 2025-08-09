#include <iostream>
#include "BFSSolver.h"

// Esta enumeração representa as cores possíveis para os vértices no algoritmo de busca em largura.
enum class Color {
    WHITE,
    GRAY,
    BLACK
};

// Esta função é responsável por executar o algoritmo de busca em largura em um grafo fornecido como entrada.
// Pré-condição: Um objeto Graph deve ser fornecido como entrada.
// Pós-condição: A função executa o algoritmo de busca em largura no grafo fornecido.
void BFSSolver::solve(Graph graph) {
    std::cout << "Insira a origem: ";
    int32_t origin;
    std::cin >> origin;

    currentGraph = graph;
    for (int i = 0; i < graph.adjList.size(); i++) {
        colors.push_back(Color::WHITE);
    }
    colors[origin] = Color::GRAY;
    grayVertex.push(origin);

    while (!grayVertex.empty()) {
        exploreVertice(grayVertex.front());
        grayVertex.pop();
    }
    std::cout << "\b\b \n";
}

// Esta função é responsável por explorar um vértice no algoritmo de busca em largura.
// Pré-condição: O índice do vértice a ser explorado deve ser fornecido como entrada.
// Pós-condição: A função explora o vértice fornecido, imprimindo-o na tela e atualizando sua cor de acordo com o algoritmo.
void BFSSolver::exploreVertice(uint32_t vertice) {
    std::cout << vertice << " - ";
    for (Edge edge : currentGraph[vertice]) {
        if (colors[edge.dest] == Color::WHITE) {
            colors[edge.dest] = Color::GRAY;
            grayVertex.push(edge.dest);
        }
    }
    colors[vertice] = Color::BLACK;
}

// Esta função é responsável por validar um grafo, retornando sempre verdadeiro.
// Pré-condição: Um objeto Graph deve ser fornecido como entrada.
// Pós-condição: A função retorna verdadeiro.
bool BFSSolver::validate(Graph graph) {
    return true;
}