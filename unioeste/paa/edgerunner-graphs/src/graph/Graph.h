#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <list>
#include <cstdint>

// Representa uma aresta do grafo, contêm um destino e um peso.
struct Edge {
public:
    int32_t dest;
    int32_t weight;

    // Inicializa uma aresta
    // Pré-condição: um destino e um peso para a aresta.
    // Pós-condição: uma aresta é inicializada.
    Edge(int32_t inDest, int32_t inWeight) : dest(inDest), weight(inWeight) {}

    // Define a comparação de maior entre duas arestas.
    friend bool operator> ( const Edge& edge1, const Edge& edge2 ) {
        return edge1.weight > edge2.weight;
    }
};

class Graph {

public:
    // Grafo representado como um vetor de lista de arestas.
    std::vector<std::list<Edge>> adjList;

    // Define se o grafo é orientado ou não.
    bool isOriented;

public:
    // Inicializa um grafo.
    // Pré-condição: nenhuma.
    // Pós-condição: É criado um grafo.
    Graph(): isOriented(false) {}

    // Inicializa um grafo.
    // Pré-condição: um booleano se o grafo é orientado e a quantidade de vétices.
    // Pós-condição: É criado um grafo.
    Graph(bool inIsOriented, int vertex): adjList(vertex), isOriented(inIsOriented) {}

    // Adiciona uma aresta ao grafo.
    // Pré-condição: Vertices de origem e destino, e o peso que da aresta.
    // Pós-condição: A aresta é adicionada ao grafo.
    void addEdge(int32_t src, int32_t dest, int32_t weight);

    // Imprime na tela os dados referentes ao grafo.
    // Pré-condição: nenhuma.
    // Pós-condição: os dados do grafo são impressos na tela.
    void print();

    // Verifica se o grafo é conectado
    // Pré-condição: nenhuma.
    // Pós-condição: retorna false se não for conectado e true se for conectado
    bool isConnected();

    // Acessa o índice da lista adjacente do grafo.
    // Pré-condição: índice da lista.
    // Pós-condição: retorna a aresta armazenada naquela posição.
    std::list<Edge>& operator[](uint32_t vertex) {
        return adjList[vertex];
    }

    // Iterador para o primeiro elemento da lista.
    // Pré-condição: nenhuma.
    // Pós-condição: retorna o início da lista.
     std::vector<std::list<Edge>>::iterator begin() {
        return adjList.begin();
    }

    // Iterador para o último elemento da lista.
    // Pré-condição: nenhuma.
    // Pós-condição: retorna o final da lista.
    std::vector<std::list<Edge>>::iterator end() {
        return adjList.end();
    }
};

#endif