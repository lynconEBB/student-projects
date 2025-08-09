#include "GraphGenerator.h"
#include <string>
#include <regex>
#include <algorithm>

// Criar um grafo com base nas informações presentes no arquivo de entrada.
// Pré-condição: um arquivo de entrada aberto e no formato correto para leitura.
// Pós-condição: retorna um grafo contendo as informações do arquivo.
Graph GraphGenerator::createGraph(std::ifstream &input) {
    bool isOriented = getIsOriented(input);
    int32_t numVertex = getNumVertex(input);
    Graph graph(isOriented, numVertex);
    setEdges(input, graph);
    return graph;
}

// Lê do arquivo se o grafo deve ser orientado ou não.
// Pré-condição: um arquivo de entrada aberto.
// Pós-condição: retorna um booleano referente se é ou não orientado.
bool GraphGenerator::getIsOriented(std::ifstream &input) {
    std::string line;
    std::getline(input, line);
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

    std::smatch matches;
    std::regex reg("orientado=([a-z]{3})");
    std::regex_search(line,matches,reg);

    if (matches.size() != 2)
        throw "Erro de formatação!";

    if ("sim" != matches.str(1) && "nao" != matches.str(1))
        throw "Erro de formatação!";

    return "sim" == matches.str(1);
}

// Lê do arquivo a quantidade de vértices que o grafo deve ter.
// Pré-condição: um arquivo de entrada aberto.
// Pós-condição: retorna o número de vértices.
int32_t GraphGenerator::getNumVertex(std::ifstream &input) {
    std::string line;
    std::getline(input, line);
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

    std::smatch matches;
    std::regex reg("V=([0-9]+)");
    std::regex_search(line,matches,reg);

    if (matches.size() != 2)
        throw "Erro de formatação!";

    return stoi(matches.str(1));
}

// Lê do arquivo as arestas e adiciona ao grafo.
// Pré-condição: um arquivo de entrada aberto.
// Pós-condição: adiciona as arestadas definidas no arquivo ao grafo.
void GraphGenerator::setEdges(std::ifstream& input, Graph& graph){
    std::string line;
    while(std::getline(input, line)){
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        std::smatch matches;
        std::regex reg("\\(([0-9]+),([0-9]+)\\):(-?[0-9]+)");
        std::regex_search(line,matches,reg);

        if (matches.size() != 4)
            throw "Erro de formatação!";

        graph.addEdge(
                stoi(matches.str(1)),
                stoi(matches.str(2)),
                stoi(matches.str(3)));
    }
}