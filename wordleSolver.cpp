#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

// open a wordBank_*.txt file and store the words in a vector
const std::vector<std::string> loadFromFile(const std::string &fileName) {
    std::ifstream infile;
    infile.open(fileName);

    if (infile.fail()) {
        throw std::invalid_argument("File not found" + fileName);
    }

    std::vector<std::string> wordBank;
    std::string word;
    while (infile >> word) {
        wordBank.push_back(word);
    }

    infile.close();
    return wordBank;
}

std::string initialState() const {
    std::cout << "MIT researchers recommend starting with SALET, " << std::endl;
    std::cout << "Other good starting words include SLATE, CRANE, SLANT, CRATE, and CARTE." << std::endl;
    std::cout << "Pick a lucky word to begin: " << std::endl;

    std::string choice = "";
    std::cin >> choice;

    return choice;
}

const std::string transitionState() {
    std::cout << "Using Green: G, Yellow: Y, Grey: R," << std::endl;
    std::cout << "Please enter the results of the guess:" << std::endl;
    std::string result = "";
    std::cin >> result;

    return result;
}

//void workingState(const std::string &str) {
//
//}

int main() {
    // load wordBank
    std::vector<std::string> wordBank = loadFromFile("wordBank_NYTimes.txt");

    std::string word = initialState();
    std::string result = transitionState();



    return 0;
}
