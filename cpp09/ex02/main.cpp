#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv) {
    PmergeMe pmerge;

    try {
        if (!pmerge.processInput(argc, argv)) {
            std::cerr << "Error" << std::endl;
            return 1;
        }

        pmerge.sortAndMeasure();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}