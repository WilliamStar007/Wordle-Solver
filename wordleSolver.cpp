#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>

uint32_t WORD_LENGTH = 5;

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

// check if a string is a word from wordBank
bool isWord(const std::string& str, const std::vector<std::string>& wordBank) {
    if (str.length() != WORD_LENGTH) {
        return false;
    }

    for (auto word: wordBank) {
        if (str == word) {
            return true;
        }
    }

    return false;
}

void suggestions(const std::vector<std::string>& wordBank) {
    std::cout << "Here are all the possibilities:" << std::endl;

    int counter = 0;
    for (auto word: wordBank) {
        std::cout << word << " ";
        ++counter;

        if (counter % 5 == 0) {
            std::cout << std::endl;
        }
        if (counter >= 20) {
            int remain = wordBank.size() - counter;
            std::cout << "Only first 20 words shown, " << remain << " words elided" << std::endl;
        }
    }
}

const std::string inputState(const std::vector<std::string>& wordBank, bool initial = false) {
    std::string choice = "";

    if (initial) {
        std::cout << "MIT researchers recommend starting with SALET, " << std::endl;
        std::cout << "Other good starting words include:" << std::endl;
        std::cout << "SLATE, CRANE, SLANT, CRATE, and CARTE." << std::endl;
        std::cout << "Pick a lucky word to begin: " << std::endl;
    }
    else {
        std::cout << "Pick a lucky word to try: " << std::endl;
    }

    std::cin >> choice;
    while (!isWord(choice, wordBank)) {
        std::cout << choice << " is not a valid word (nonexistent/excluded)." << std::endl;
        std::cout << "Please enter a existing 5-letter word: " << std::endl;
        std::cin >> choice;
    }

    return choice;
}

const std::string transitionState() {
    std::cout << "Using Green: G, Yellow: Y, Grey: R," << std::endl;
    std::cout << "Please enter the results of the guess: " << std::endl;
    std::string result = "";
    std::cin >> result;

    return result;
}

// core function to
bool workingState(const std::string& guess, const std::string& result, std::vector<std::string>& wordBank) {
    std::unordered_map<int, char> green;
    std::unordered_map<char, int> yellow;
    std::set<char> red;

    if (result == "GGGGG") {
        return true;
    }

    for (uint32_t i = 0; i < WORD_LENGTH; ++i) {
        if (result[i] == 'R') {
            red.insert(guess[i]);
        }
        else if (result[i] == 'G') {
            green[i] = guess[i];
        }
        else {
            yellow[guess[i]] += 1;
        }
    }

    auto it = wordBank.begin();
    while (it != wordBank.end()) {
        bool removed = false;

        // check for non-existent letter
        for (auto c: red) {
            if (it->find(c) != (uint32_t) -1) {
                it = wordBank.erase(it);
                removed = true;
                break;
            }
        }
        if (removed) {
            continue;
        }

        // check for letter position
        for (auto i: green) {
            if ((*it)[i.first] != i.second) {
                it = wordBank.erase(it);
                removed = true;
                break;
            }
        }
        if (removed) {
            continue;
        }

        // check for letter occurrence
        for (auto i: yellow) {
            int num = std::count(it->begin(), it->end(), i.first);
            if (num < i.second) {
                it = wordBank.erase(it);
                removed = true;
                break;
            }
        }
        if (not removed) {
            ++it;
        }
    }

//    std::cout << "word bank" << std::endl;
//    for (auto word: wordBank) {
//        std::cout << word << std::endl;
//    }

    suggestions(wordBank);

    return false;
}

int main() {
    // load wordBank
    std::vector<std::string> wordBank = loadFromFile("wordBank_OG.txt");

    std::string word = inputState(wordBank, true);
    std::string result = transitionState();
    bool success = workingState(word, result, wordBank);

    while (!success) {
        word = inputState(wordBank);
        result = transitionState();
    }

    std::cout << word << result;

    return 0;
}
