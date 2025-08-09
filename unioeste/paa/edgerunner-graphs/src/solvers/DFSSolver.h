#ifndef GRAPHS_DFSSOLVER_H
#define GRAPHS_DFSSOLVER_H
#include "Solver.h"
#include <vector>

enum class Color;

// Classe responsável por aplicar o algoritmo DFS em um grafo
class DFSSolver : public Solver
{
public:
    // Esta função é responsável por validar um grafo, retornando sempre verdadeiro.
    // Pré-condição: Um objeto Graph deve ser fornecido como entrada.
    // Pós-condição: A função retorna verdadeiro.
    void solve(Graph graph) override;

    // Esta função é responsável por executar o algoritmo de busca em profundidade em um grafo fornecido como entrada.
    // Pré-condição: Um objeto Graph deve ser fornecido como entrada.
    // Pós-condição: A função executa o algoritmo de busca em profundidade no grafo fornecido.
    bool validate(Graph graph) override;

private:
    // Esta função é responsável por visitar um vértice no algoritmo de busca em profundidade.
    // Pré-condição: O índice do vértice a ser visitado deve ser fornecido como entrada.
    // Pós-condição: A função visita o vértice fornecido, adicionando-o à lista de visitas e atualizando sua cor de acordo com o algoritmo
    void visit(uint32_t index);

private:
    // Vertices visitados
    std::list<uint32_t> visits;
    // Cor de cada vertice
    std::vector<Color> colors;
    // Grafo atual
    Graph currentGraph;
};

#endif