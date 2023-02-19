#include "wordleSolver.h"

const uint32_t ATTEMPTS = 6;
const uint32_t WORD_LENGTH = 5;

// class constructor
WordleSolver::WordleSolver(std::string filename): success(false), attempts(ATTEMPTS) {
    loadFromFile(filename);
}

// attempt to solve wordle
// return whether solved successfully
bool WordleSolver::solve() {
    inputState();
    transitionState();
    workingState();

    while (attempts && !success) {
        inputState();
        transitionState();
        workingState();
    }

    return success;
}

// open a wordBank_*.txt file and store words in wordBank
void WordleSolver::loadFromFile(const std::string &fileName) {
    std::ifstream infile;
    infile.open(fileName);

    if (infile.fail()) {
        throw std::invalid_argument("File not found " + fileName);
    }

    std::string word;
    while (infile >> word) {
        wordBank.insert(word);
    }

    infile.close();
}

// transforms input string to lower case
// check if a string is a word from wordBank
bool WordleSolver::isWord(std::string& str) {
    if (str.length() != WORD_LENGTH) {
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return wordBank.find(str) != wordBank.end();
}

// transforms input string to upper case
// check if a string is a valid result for a guess
bool WordleSolver::isResult(std::string& res) {
    if (res.length() != WORD_LENGTH) {
        return false;
    }

    std::transform(res.begin(), res.end(), res.begin(), ::toupper);
    return res.find_first_not_of("GYR") == std::string::npos;
}

// take user input from terminal
void WordleSolver::inputState() {
    // initial Message
    if (attempts == ATTEMPTS) {
        std::cout << "MIT researchers recommend starting with SALET" << std::endl;
        std::cout << "Other good starting words include:" << std::endl;
        std::cout << "SLATE, CRANE, SLANT, CRATE, and CARTE." << std::endl;
    }

    // ask user input
    std::cout << "Pick a lucky word: " << std::endl;
    std::cin >> word_choice;
    while (!isWord(word_choice)) {
        std::cout << word_choice << " is not a valid word (nonexistent/excluded)." << std::endl;
        std::cout << "Please enter a valid 5-letter word: " << std::endl;
        std::cin >> word_choice;
    }

    // remove word_choice from wordBank
    wordBank.erase(word_choice);

    // update variable
    --attempts;
}

// ask user for result
void WordleSolver::transitionState() {
    std::cout << "Using Green: G, Yellow: Y, Grey: R," << std::endl;
    std::cout << "Please enter the results of the guess: " << std::endl;
    std::cin >> guess_result;

    while (!isResult(guess_result)) {
        std::cout << guess_result << " is not a valid result." << std::endl;
        std::cout << "Using Green: G, Yellow: Y, Grey: R," << std::endl;
        std::cout << "Please enter the results of the guess: " << std::endl;
        std::cin >> guess_result;
    }
}

// remove words from wordBank based on guess and result
void WordleSolver::workingState() {
    // correct char position
    std::unordered_map<int, char> green;
    // minimum occurrence of a char
    std::unordered_map<char, int> yellow_green;
    // incorrect char position
    std::unordered_map<int, char> yellow_red;
    // maximum occurrence of a char
    std::unordered_map<char, int> red;

    // solved!
    if (guess_result == "GGGGG") {
        success = true;
        return;
    }

    for (uint32_t i = 0; i < WORD_LENGTH; ++i) {
        // grey slots
        if (guess_result[i] == 'R') {
            red[word_choice[i]] = 0;
        }
        // yellow slots
        else if (guess_result[i] == 'Y') {
            yellow_green[word_choice[i]] += 1;
            yellow_red[i] = word_choice[i];
        }
    }

    for (uint32_t i = 0; i < WORD_LENGTH; ++i) {
        // green slots
        if (guess_result[i] == 'G') {
            green[i] = word_choice[i];
            yellow_green[word_choice[i]] += 1;
            if (red.count(word_choice[i])) {
                red[word_choice[i]] += 1;
            }
        }
    }

    // remove words based on conditions above
    auto it = wordBank.begin();
    while (it != wordBank.end()) {
        bool removed = false;

        // check for non-existent letter
        for (auto i: red) {
            int num = std::count(it->begin(), it->end(), i.first);
            if (num > i.second) {
                it = wordBank.erase(it);
                removed = true;
                break;
            }
        }
        if (removed) {
            continue;
        }

        // check for correct letter position
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

        // check for incorrect letter position
        for (auto i: yellow_red) {
            if ((*it)[i.first] == i.second) {
                it = wordBank.erase(it);
                removed = true;
                break;
            }
        }
        if (removed) {
            continue;
        }

        // check for letter occurrence
        for (auto i: yellow_green) {
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

    // get suggestions
    suggestions();
}

// list possible words and make suggestions
void WordleSolver::suggestions() {
    if (wordBank.empty()) {
        std::cout << "Check the earlier inputs!" << std::endl;
        throw std::domain_error("Impossible situation");
    }

    // solved!
    if (wordBank.size() == 1) {
        std::cout << "There is only one possibility: " << *wordBank.begin() << std::endl;
        success = true;
        return;
    }

    std::cout << "Here are all the possibilities:" << std::endl;

    int counter = 0;
    for (auto word: wordBank) {
        std::cout << word << " ";
        ++counter;

        if (counter % 6 == 0) {
            std::cout << std::endl;
        }
        if (counter >= 30) {
            int remain = wordBank.size() - counter;
            std::cout << remain << " words elided..." << std::endl;;
            break;
        }
    }

    // output spacing
    if (counter % 6 != 0) {
        std::cout << std::endl;
    }
}
