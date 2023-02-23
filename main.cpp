#include "wordleSolver.h"

int main() {
    // initiate WordleSolver
    std::cout << "Enter the name of a txt file as work bank:" << std::endl;
    std::string bankFile;
    std::cin >> bankFile;
    WordleSolver solver(bankFile);
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
