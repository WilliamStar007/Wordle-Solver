#include "wordleSolver.h"

int main() {
    WordleSolver solver;
    bool outcome = solver.solve();

    if (outcome) {
        std::cout << "Great Job!!" << std::endl;
    }
    else {
        std::cout << "So close!" << std::endl;
    }

    return 0;
};
