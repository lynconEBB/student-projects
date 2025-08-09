#ifndef GRAPHS_FLOYDWARSHALL_H
#define GRAPHS_FLOYDWARSHALL_H
#include "Solver.h"
#include <vector>


class FloydWarshallSolver : public Solver{
    using Matrix = std::vector<std::vector<int32_t>>;

public:
    // Resolve o problema do caminho mínimo utilizando o algoritmo de Floid-Warshall.
    // Pré-condição: o grafo deve estar devidamente inicializado.
    // Pós-condição: a solução para o problema do caminho mais curto é impressa na tela.
    void solve(Graph graph) override;

    // Verifica se o grafo de entrada é válido para o algoritmo de Floid-Warshall.
    // Pré-condição: o grafo deve estar devidamente inicializado.
    // Pós-condição: retorna true se o grafo atende às condições e false caso contrário.
    bool validate(Graph graph) override;

private:
    // Inicializa as matrizes de distância e próximo.
    // Pré-condição: o grafo deve estar devidamente inicializado e as matrizes de distâncias e próximo declaradas.
    // Pós-condição: matrizes preenchidas com valores padrão.
    void initializeMatrix(Graph graph, Matrix& distance, Matrix& next);

    // Calcula a menor distância entre cada par de vértices usando o algoritmo de Floyd-Warshall.
    // Pré-condição: quantidade de vertices no grafo, matrizes de distância e próximo inicializadas corretamente.
    // Pós-condição: matriz de distância e próximo atualizada com as menores distâncias entre cada par de vértices.
    void minDistance(int32_t size, Matrix& distance, Matrix& next);

    // Verifica se há ciclo negativo no grafo a partir da matriz de distância calculada.
    // Pré-condição: matriz de distância calculada corretamente.
    // Pós-condição: retorna verdadeiro se houver ciclo negativo, falso caso contrário.
    bool hasNegativeCycle(Matrix distance);

    // Imprime a matriz de distância calculada.
    // Pré-condição: quantidade de vertices no grafo, matriz de distância calculada corretamente.
    // Pós-condição: a matriz de distância é impressa na tela.
    void printMatrix(int32_t size, Matrix distance);

    // Imprime o caminho mínimo entre cada par de vértices.
    // Pré-condição: quantidade de vertices no grafo, matriz de próximo calculada corretamente.
    // Pós-condição: o caminho mínimo entre cada par de vértices é impressa na tela.
    void printPath(int32_t size, Matrix next);

};


#endif
