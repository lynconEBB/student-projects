#ifndef GRAPHS_PRIMSOLVER_H
#define GRAPHS_PRIMSOLVER_H

#include "Solver.h"
#include <utility>
#include <vector>
#include <queue>
#include <limits>
#include <string>

// Estrutura que representa um vértice no algoritmo de Prim
struct PrimVertice {
public:
    // Numero identificador do vertice
    int32_t num;
    // Lista de arestas adjacentes ao vertice
    std::list<Edge> edges;
    // Chava utilizada no algoritmo
    int32_t key;
    // Vertice precedente
    int32_t prev;
    // Indica se o vertice ainda esta na fila de prioridade
    bool inQueue;

    PrimVertice(int32_t num, const std::list<Edge>& edges) :
            num(num), edges(edges),
            key(std::numeric_limits<int32_t>::max()), prev(-1), inQueue(true) {}

    PrimVertice(int32_t num, const std::list<Edge>& edges, int32_t key) :
            num(num), edges(edges),
            key(key), prev(-1), inQueue(true) {}

};

// Operador de inserção em stream para um objeto PrimVertice
// Pré-condição: Nenhuma
// Pós-condição: a representação em string do objeto PrimVertice é inserida na stream de saída.
std::ostream& operator<<(std::ostream& os, const PrimVertice& vertice);

// Estrutura de comparação de ponteiros para objetos PrimVertice, usada em uma priority_queue
// Pré-condição: os ponteiros v1 e v2 devem apontar para objetos PrimVertice válidos
// Pós-condição: retorna true se a chave do objeto apontado por v1 é maior do que a chave do objeto apontado por v2.
struct ComparePrimVerticePointer {
    bool operator()(const PrimVertice* v1, const PrimVertice* v2) const {
        return v1->key > v2->key;
    }
};

// Classe que implementa o algoritmo de Prim para encontrar a árvore geradora mínima de um grafo
class PrimSolver : public Solver
{
public:
    // Executa o algoritmo de Prim no grafo passado como parâmetro e armazena a árvore geradora mínima encontrada internamente na classe
    // Pré-condição: o grafo passado como parâmetro deve ser válido.
    // Pós-condição: a solução do problema é armazenada na classe e apresentada, podendo ser acessada pelos métodos públicos.
    void solve(Graph graph) override;

    // Valida se o grafo passado como parâmetro é não orientado e conexo.
    // Pré-condição: o grafo passado como parâmetro deve ser válido.
    // Pós-condição: retorna verdadeiro se o grafo é não orientado e conexo, falso caso contrário.
    bool validate(Graph graph) override;

private:
    // Escreve a árvore geradora mínima armazenada internamente na classe em um arquivo de saída com nome definido pela constante
    // Pré-condição: a solução do problema deve ter sido armazenada na classe PrimSolver.
    // Pós-condição: o resultado da solução é impresso na saída padrão e um arquivo de imagem é gerado.
    void outputResult();
    // Calcula o peso total da árvore geradora mínima armazenada internamente na classe.
    // Pré-condição: a solução do problema deve ter sido armazenada na classe PrimSolver.
    // Pós-condição: Retorna o peso total baseado no resultado calculado
    int32_t getTotalWeight();

private:
    // constante string que representa o nome padrão do arquivo de saída da árvore geradora mínima.
    const static std::string DEFAULT_OUT_FILE;
    // deque de objetos PrimVertice que armazena os vértices do grafo
    std::deque<PrimVertice> vertices;
    // Fila de prioridade de ponteiros para objetos PrimVertice, usada para armazenar os vértices com as menores chaves.
    std::priority_queue<PrimVertice*, std::vector<PrimVertice*>, ComparePrimVerticePointer> queue;
};

#endif