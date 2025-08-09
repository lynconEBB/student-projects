#ifndef GRAPHS_BFSSOLVER_H
#define GRAPHS_BFSSOLVER_H
#include "Solver.h"
#include <vector>
#include <queue>

enum class Color;

// A classe BFSSolver é responsável por resolver o problema
// do caminho mínimo em um grafo usando o algoritmo de busca em largura.
class BFSSolver: public Solver {

public:
    // Esta função é responsável por executar o algoritmo de busca em largura em um grafo fornecido como entrada.
    // Pré-condição: Um objeto Graph deve ser fornecido como entrada.
    // Pós-condição: A função executa o algoritmo de busca em largura no grafo fornecido.
    void solve(Graph graph) override;

    // Esta função é responsável por validar um grafo, retornando sempre verdadeiro.
    // Pré-condição: Um objeto Graph deve ser fornecido como entrada.
    // Pós-condição: A função retorna verdadeiro.
    bool validate(Graph graph) override;

private:
    // Grafo carregado
    Graph currentGraph;
    // Fila contendo os vertices cinzas
    std::queue<uint32_t> grayVertex;
    // Cor de cada vertice
    std::vector<Color> colors;

private:
    // Esta função é responsável por explorar um vértice no algoritmo de busca em largura.
    // Pré-condição: O índice do vértice a ser explorado deve ser fornecido como entrada.
    // Pós-condição: A função explora o vértice fornecido, imprimindo-o na tela e atualizando sua cor de acordo com o algoritmo.
    void exploreVertice(uint32_t vertice);
};

#endif