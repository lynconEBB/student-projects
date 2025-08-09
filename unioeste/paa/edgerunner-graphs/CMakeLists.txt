cmake_minimum_required(VERSION 3.22)
project(graphs)

set(CMAKE_CXX_STANDARD 11)

include(FindGraphviz.cmake)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(edgerunner src/main.cpp src/graph/GraphGenerator.cpp src/graph/GraphGenerator.h src/App.cpp src/App.h src/solvers/Solver.cpp src/solvers/Solver.h src/graph/Graph.cpp src/graph/Graph.h src/solvers/DFSSolver.cpp src/solvers/DFSSolver.h src/solvers/BFSSolver.cpp src/solvers/BFSSolver.h src/solvers/KruskalSolver.cpp src/solvers/KruskalSolver.h src/solvers/PrimSolver.cpp src/solvers/PrimSolver.h src/solvers/FloydWarshallSolver.cpp src/solvers/FloydWarshallSolver.h src/solvers/DijkstraSolver.cpp src/solvers/DijkstraSolver.h src/solvers/BellmanFordSolver.cpp src/solvers/BellmanFordSolver.h)

target_include_directories(edgerunner PUBLIC ${GRAPHVIZ_INCLUDE_DIRS} src)
target_link_libraries(edgerunner  PUBLIC ${GRAPHVIZ_GVC_LIBRARY} ${GRAPHVIZ_CGRAPH_LIBRARY})