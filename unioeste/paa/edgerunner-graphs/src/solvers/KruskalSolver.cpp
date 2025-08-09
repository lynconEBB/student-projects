#include "KruskalSolver.h"
#include <ostream>
#include <iostream>
#include <queue>
#include "gvc.h"
#include <cgraph.h>
#include <string>

// Sobrecarga do operador de inserção em stream para a classe KruskalEdge
// Pré-condição: a instância da KruskalEdge deve ser válida e conter os valores dos vértices de origem e destino.
// Pós-condição: a aresta KruskalEdge é inserida na saída de fluxo de forma formatada.
std::ostream& operator<<(std::ostream& os, const KruskalEdge& edge) {
    os << "(" << edge.src << ", " << edge.dst << ")";
    return os;
}

// Resolve o problema de árvore geradora mínima utilizando o algoritmo de Kruskal.
// Pré-condição: o grafo passado como parâmetro deve ser válido.
// Pós-condição: a solução do problema é armazenada na classe e apresentada, podendo ser acessada pelos métodos públicos.
void KruskalSolver::solve(Graph graph) {
    for (int i = 0; i < graph.adjList.size(); i++){
        sets.push_back(i);
        for (Edge edge : graph[i]) {
            if (edge.dest >= i)
                sortedEdges.insert({i, edge.dest, edge.weight});
        }
    }

    for (const KruskalEdge& edge : sortedEdges) {
        if (sets[edge.src] != sets[edge.dst]) {
            finalWeight += edge.weight;
            edge.inSpammingTree = true;
            joinSets(sets[edge.src], sets[edge.dst]);
        }
    }

    outputResult();
}

// Imprime o resultado da solução do problema de árvore geradora mínima utilizando o algoritmo de Kruskal.
// Pré-condição: a solução do problema deve ter sido armazenada na classe KruskalSolver.
// Pós-condição: o resultado da solução é impresso na saída padrão e um arquivo de imagem é gerado.
void KruskalSolver::outputResult() {

    std::cout << "peso total: " << finalWeight << '\n';
    std::cout << "arestas: ";

    Agraph_t* g = agopen("G", Agundirected, nullptr);
    agsafeset(g, "label", "Kruskal Spamming Tree", "");
    agsafeset(g, "fontname", "Arial", "");

    for (const KruskalEdge& edge : sortedEdges) {


        char* nodeName1 = const_cast<char*>(std::to_string(edge.src).c_str());
        Agnode_t* n1 =  agnode(g, nodeName1, TRUE);
        char* nodeName2 = const_cast<char*>(std::to_string(edge.dst).c_str());
        Agnode_t* n2 = agnode(g, nodeName2, TRUE);

        Agedge_t* e = agedge(g,n1,n2,"", TRUE);
        char* weightStr = const_cast<char*>(std::to_string(edge.weight).c_str());
        agsafeset(e, "label", weightStr,"");
        if (edge.inSpammingTree) {
            std::cout << edge << ",";
            agsafeset(e, "color", "red", "");
            agsafeset(e, "fontcolor", "red","");
        }
    }
    std::cout << "\b ";

    GVC_t* gvc = gvContext();
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "png", "kruskalResult.png");
    agclose(g);
    gvFreeContext(gvc);
}

// Une dois conjuntos de vértices em um único conjunto.
// Pré-condição: os dois conjuntos devem ser válidos e diferentes.
// Pós-condição: os dois conjuntos são unidos em um único conjunto.
void KruskalSolver::joinSets(uint32_t set1, uint32_t set2) {
    for (uint32_t& set : sets) {
        if (set == set1)
            set = set2;
    }
}

// Valida se o grafo passado como parâmetro é não orientado e conexo.
// Pré-condição: o grafo passado como parâmetro deve ser válido.
// Pós-condição: retorna verdadeiro se o grafo é não orientado e conexo, falso caso contrário.
bool KruskalSolver::validate(Graph graph) {
    if (graph.isOriented) {
        std::cout << "Nao e possivel aplicar o algoritmo de Kruskal - grafo e orientado!!\n";
        return false;
    }
    if (!graph.isConnected()) {
        std::cout << "Nao e possivel aplicar o algoritmo de Kruskal - grafo nao e conectado!!\n";
        return false;
    }
    return true;
}
