#include "wordleSolver.h"

int main() {
    WordleSolver solver;
    bool outcome = solver.solve();

    // output spacing
    std::cout << std::endl;

    if (outcome) {
        // "phew" if solved on last attempt
        std::string phew = solver.getAttempts()? "" : "Phew, ";
        std::cout << phew << "Great Job!!" << std::endl;
    }
    else {
        std::cout << "So close!" << std::endl;
    }

    return 0;
};
