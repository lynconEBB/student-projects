#ifndef GRAPHS_KRUSKALSOLVER_H
#define GRAPHS_KRUSKALSOLVER_H

#include "Solver.h"
#include <set>

// Estrutura representando uma aresta com as informações necessárias para a realização do algoritmo de Kruskal
struct KruskalEdge {
public:
    // Vertice de origem
    int32_t src;
    // Vertice de destino
    int32_t dst;
    // Peso da aresta
    int32_t weight;
    // Indica se o vertice faz parte da arvore geradora
    mutable bool inSpammingTree;

    // Construtor padrão
    KruskalEdge(int32_t src, int32_t dst, int32_t weight) : src(src), dst(dst), weight(weight), inSpammingTree(false) {}

    // Sobrecarga do operador < para comparação direta
    bool operator<(const KruskalEdge& other) const {
        return weight < other.weight;
    }
};

class KruskalSolver: public Solver
{
public:
    // Resolve o problema de árvore geradora mínima utilizando o algoritmo de Kruskal.
    // Pré-condição: o grafo passado como parâmetro deve ser válido.
    // Pós-condição: a solução do problema é armazenada na classe e apresentada, podendo ser acessada pelos métodos públicos.
    void solve(Graph graph) override;

    // Valida se o grafo passado como parâmetro é não orientado e conexo.
    // Pré-condição: o grafo passado como parâmetro deve ser válido.
    // Pós-condição: retorna verdadeiro se o grafo é não orientado e conexo, falso caso contrário.
    bool validate(Graph graph) override;

private:
    // Une dois conjuntos de vértices em um único conjunto.
    // Pré-condição: os dois conjuntos devem ser válidos e diferentes.
    // Pós-condição: os dois conjuntos são unidos em um único conjunto.
    void joinSets(uint32_t set1, uint32_t set2);
    // Imprime o resultado da solução do problema de árvore geradora mínima utilizando o algoritmo de Kruskal.
    // Pré-condição: a solução do problema deve ter sido armazenada na classe KruskalSolver.
    // Pós-condição: o resultado da solução é impresso na saída padrão e um arquivo de imagem é gerado.
    void outputResult();

private:
    // Arestas ordenadas
    std::multiset<KruskalEdge> sortedEdges;
    // Representação dos conjuntos de vertices
    std::vector<uint32_t> sets;
    // Peso final da arvore geradora minima
    int32_t finalWeight = 0;

};

#endif