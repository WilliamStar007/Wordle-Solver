#include "wordleSolver.h"

int main() {
    WordleSolver solver;
    bool outcome = solver.solve();

    // output spacing
    std::cout << std::endl;

    if (outcome) {
        std::cout << "Great Job!!" << std::endl;
    }
    else {
        std::cout << "So close!" << std::endl;
    }

    return 0;
};
