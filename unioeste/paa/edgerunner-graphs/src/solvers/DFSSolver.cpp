#include <iostream>
#include "DFSSolver.h"

// Esta estrutura de dados representa as cores possíveis para os vértices no algoritmo de busca em profundidade.
enum class Color {
    WHITE,
    GRAY,
    BLACK
};
// Esta função é responsável por validar um grafo, retornando sempre verdadeiro.
// Pré-condição: Um objeto Graph deve ser fornecido como entrada.
// Pós-condição: A função retorna verdadeiro.
bool DFSSolver::validate(Graph graph)
{
    return true;
}

// Esta função é responsável por executar o algoritmo de busca em profundidade em um grafo fornecido como entrada.
// Pré-condição: Um objeto Graph deve ser fornecido como entrada.
// Pós-condição: A função executa o algoritmo de busca em profundidade no grafo fornecido.
void DFSSolver::solve(Graph graph) {
    std::cout << "Insira a origem: ";
    int32_t origin;
    std::cin >> origin;

    currentGraph = graph;

    for (int i = 0; i < currentGraph.adjList.size(); i++) {
        colors.push_back(Color::WHITE);
    }

    for (int i = origin; i < graph.adjList.size(); i++) {
        if (colors[i] == Color::WHITE) {
            visit(i);
        }
    }
    for (int i = 0; i < origin; i++) {
        if (colors[i] == Color::WHITE) {
            visit(i);
        }
    }
    std::cout << "\b\b ";
}

// Esta função é responsável por visitar um vértice no algoritmo de busca em profundidade.
// Pré-condição: O índice do vértice a ser visitado deve ser fornecido como entrada.
// Pós-condição: A função visita o vértice fornecido, adicionando-o à lista de visitas e atualizando sua cor de acordo com o algoritmo
void DFSSolver::visit(uint32_t index) {
    colors[index] = Color::GRAY;
    visits.push_back(index);
    std::cout << index << " - ";
    for(Edge edge : currentGraph.adjList[index]) {
        if (colors[edge.dest] == Color::WHITE) {
            visit(edge.dest);
        }
    }
    colors[index] = Color::BLACK;
}