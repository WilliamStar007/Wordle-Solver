#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

// open a wordBank.txt file
// read the file line by line
// store the words in a vector
// close the file
// return the vector

std::vector<std::string> loadFromFile(const std::string &fileName) {
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

bool isWord(const std::vector<std::string> &wordBank, const std::string &word) {
    for (const auto &w : wordBank) {
        if (w == word) {
            return true;
        }
    }
    return false;
}


