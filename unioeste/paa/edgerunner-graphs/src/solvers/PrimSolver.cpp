#include <iostream>
#include "PrimSolver.h"
#include <gvc.h>
#include <cgraph.h>

// Valida se o grafo passado como parâmetro é não orientado e conexo.
// Pré-condição: o grafo passado como parâmetro deve ser válido.
// Pós-condição: retorna verdadeiro se o grafo é não orientado e conexo, falso caso contrário.
bool PrimSolver::validate(Graph graph) {
    if (graph.isOriented) {
        std::cout << "Nao e possivel aplicar o algoritmo de Prim - grafo e orientado!!\n";
        return false;
    }
    if (!graph.isConnected()) {
        std::cout << "Nao e possivel aplicar o algoritmo de Prim - grafo nao e conectado!!\n";
        return false;
    }
    return true;
}

// Executa o algoritmo de Prim no grafo passado como parâmetro e armazena a árvore geradora mínima encontrada internamente na classe
// Pré-condição: o grafo passado como parâmetro deve ser válido.
// Pós-condição: a solução do problema é armazenada na classe e apresentada, podendo ser acessada pelos métodos públicos.
void PrimSolver::solve(Graph graph) {
    int32_t origin;
    std::cout << "Vertice inicial: ";
    std::cin >> origin;

    for (int i = 0; i < graph.adjList.size(); i++) {
        if (i == origin)
            vertices.emplace_back(i,graph[i], 0);
        else
            vertices.emplace_back(i,graph[i]);
        queue.push(&vertices[i]);
    }

    while (!queue.empty()) {
        PrimVertice& vertice = *queue.top();

        for (Edge edge : vertice.edges) {
            PrimVertice& adjVertice = vertices[edge.dest];

            if (adjVertice.inQueue && edge.weight < adjVertice.key) {
                adjVertice.prev = vertice.num;
                adjVertice.key = edge.weight;
            }
        }

        // Remove o primeiro elemento e força a reordenação da fila inteira
        queue.pop();
        vertice.inQueue = false;
        std::make_heap(const_cast<PrimVertice**>(&queue.top()),
                       const_cast<PrimVertice**>(&queue.top() + queue.size()),
                       ComparePrimVerticePointer());
    }

    outputResult();
}

// Calcula o peso total da árvore geradora mínima armazenada internamente na classe.
// Pré-condição: a solução do problema deve ter sido armazenada na classe PrimSolver.
// Pós-condição: Retorna o peso total baseado no resultado calculado
int32_t PrimSolver::getTotalWeight() {
    int32_t sum = 0;

    for (const PrimVertice& vertice : vertices) {
        if (vertice.prev != -1)
            sum += vertice.key;
    }

    return sum;
}

const std::string PrimSolver::DEFAULT_OUT_FILE = "primResult.png";

// Escreve a árvore geradora mínima armazenada internamente na classe em um arquivo de saída com nome definido pela constante
// Pré-condição: a solução do problema deve ter sido armazenada na classe PrimSolver.
// Pós-condição: o resultado da solução é impresso na saída padrão e um arquivo de imagem é gerado.
void PrimSolver::outputResult() {
    std::cout << "peso total: " << getTotalWeight() << '\n';

    Agraph_t* g = agopen("G", Agundirected, nullptr);
    agsafeset(g, "label", "Prim Spamming Tree", "");
    agsafeset(g, "fontname", "Arial", "");
    agsafeset(g, "rankdir", "LR", "");
    agsafeset(g, "nodesep", "0.5", "");

    for (const PrimVertice& vertice : vertices) {
        char* verticeName1 = const_cast<char*>(std::to_string(vertice.num).c_str());
        Agnode_t* v1 =  agnode(g, verticeName1, TRUE);
        agsafeset(v1, "shape", "circle", "");

        for (Edge edge : vertice.edges) {
            if (edge.dest < vertice.num)
                continue;

            char* verticeName2 = const_cast<char*>(std::to_string(edge.dest).c_str());
            Agnode_t* v2 =  agnode(g, verticeName2, TRUE);
            agsafeset(v2, "shape", "circle", "");

            Agedge_t* e = agedge(g,v1,v2,"", TRUE);
            char* weight = const_cast<char*>(std::to_string(edge.weight).c_str());
            agsafeset(e, "label", weight,"");

            // Pinta de vermelho caso seja vertice adicionado a arvore geradora
            if (edge.dest == vertice.prev || vertices[edge.dest].prev == vertice.num){
                std::cout << vertice << ",";
                agsafeset(e, "color", "red", "");
                agsafeset(e, "fontcolor", "red","");
            }
        }

    }
    std::cout << "\b \n";

    GVC_t* gvc = gvContext();
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", DEFAULT_OUT_FILE.c_str());
    agclose(g);
    gvFreeContext(gvc);

    std::cout << "Desenho da arvore produzido no arquivo: " << DEFAULT_OUT_FILE;
}

// Operador de inserção em stream para um objeto PrimVertice
// Pré-condição: Nenhuma
// Pós-condição: a representação em string do objeto PrimVertice é inserida na stream de saída.
std::ostream& operator<<(std::ostream& os, const PrimVertice& vertice) {
    os << "(" << vertice.prev << ", " << vertice.num << ")";
    return os;
}