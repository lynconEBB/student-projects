#ifndef GRAPHS_APP_H
#define GRAPHS_APP_H

#include <fstream>
#include "graph/Graph.h"
#include "graph/GraphGenerator.h"
#include <memory>

class Solver;

// Opçoes de execução disponivies ao usuário
enum class Option {
    LOAD = 1,
    DRAW = 2,
    DFS = 3,
    BFS = 4,
    DIJKSTRA = 5,
    BELLMANFORD = 6,
    FLOYDWARSHALL = 7,
    KRUSKAL = 8,
    PRIM = 9,
    EXIT = 10
};

// Responsável por executar a aplicação e gerenciar as interações com o usuário.
class App {
public:
    // Essa função é responsável por iniciar a execução da aplicação e gerenciar todas as interações com o usuário
    // Pré-condição: Nenhuma informação adicional é necessária.
    // Pós-condição: A aplicação é executada e as interações com o usuário são gerenciadas
    void run();

private:
    // Essa função é responsável por solicitar ao usuário o nome do arquivo de configuração a ser lido.
    // Pré-condição: Um objeto ifstream é passado por referência como parâmetro.
    // Pós-condição: O usuário fornece o nome do arquivo de configuração, que é aberto e atribuído ao objeto ifstream.
    void requestFile(std::ifstream &configFile);

    // Essa função é responsável por solicitar ao usuário que escolha uma opção do menu.
    // Pré-condição: Nenhuma informação adicional é necessária.
    // Pós-condição: O usuário escolhe uma opção do menu e a opção é armazenada em uma variável.
    void requestOption();

    // Essa função é responsável por executar a opção escolhida pelo usuário.
    // Pré-condição: Uma opção válida foi selecionada.
    // Pós-condição: A opção escolhida pelo usuário é executada.
    void executeOption();

    // Essa função é responsável por exibir o menu de opções disponíveis para o usuário.
    // Pré-condição: Nenhuma informação adicional é necessária.
    // Pós-condição: O menu é exibido na tela.
    void printMenu();

    // Desenha o grafo carregado atualmente para o arquivo padrão
    // Pré-condição: Grafo carregado previamente
    // Pós-condição: Arquivo contendo a imagem do grafo criado
    void drawGraphToDefaultFile();

private:
    static const std::string DEFAULT_OUT_FILE;
    // A variável indica se um grafo foi carregado na memória.
    bool hasGraphLoaded = false;
    // A variável armazena a opção escolhida pelo usuário.
    Option option;
    // A variável armazena o solucionador atualmente em uso.
    std::shared_ptr<Solver> currentSolver;
    // A variável armazena o grafo atualmente carregado na memória.
    Graph currentGraph;
    // A variável é responsável por gerar grafos aleatórios quando necessário.
    GraphGenerator graphGenerator;
};

#endif