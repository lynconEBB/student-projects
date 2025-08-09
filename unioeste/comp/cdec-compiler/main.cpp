#include <iostream>
#include <unordered_map>
#include <iostream>
#include "driver.h"


int main(int argc, char* argv[]) {
     if (argc < 2) {
        std::cout << "Missing parameter!!\n";
        exit(1);
    }
    std::ifstream file(argv[1], std::fstream::in);

    if (!file.good()){
        std::cout << "Cannot find specified file!!\n";
        exit(1);
    }

    Cd::Driver driver(file, argv[1]);
    driver.init();

    return 0;
}