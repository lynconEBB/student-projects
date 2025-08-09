#ifndef GRAPHS_GRAPHGENERATOR_H
#define GRAPHS_GRAPHGENERATOR_H

#include <fstream>
#include "Graph.h"


class GraphGenerator {
public:
    // Criar um grafo com base nas informações presentes no arquivo de entrada.
    // Pré-condição: um arquivo de entrada aberto e no formato correto para leitura.
    // Pós-condição: retorna um grafo contendo as informações do arquivo.
    Graph createGraph(std::ifstream& input);
private:
    // Lê do arquivo se o grafo deve ser orientado ou não.
    // Pré-condição: um arquivo de entrada aberto.
    // Pós-condição: retorna um booleano referente se é ou não orientado.
    bool getIsOriented(std::ifstream& input);

    // Lê do arquivo a quantidade de vértices que o grafo deve ter.
    // Pré-condição: um arquivo de entrada aberto.
    // Pós-condição: retorna o número de vértices.
    int32_t getNumVertex(std::ifstream& input);

    // Lê do arquivo as arestas e adiciona ao grafo.
    // Pré-condição: um arquivo de entrada aberto.
    // Pós-condição: adiciona as arestadas definidas no arquivo ao grafo.
    void setEdges(std::ifstream& input, Graph& graph);
};

#endif