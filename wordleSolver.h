#ifndef WORDLE_SOLVER_WORDLESOLVER_H
#define WORDLE_SOLVER_WORDLESOLVER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <stdexcept>

// wordle solver class
class WordleSolver {
    public:
        // class constructor
        explicit WordleSolver(std::string filename="wordBank_OG.txt");

        // attempt to solve wordle
        // return whether solved successfully
        bool solve();

    private:
        // load wordBank from file
        void loadFromFile(const std::string &fileName);

        // check if a string is a word from wordBank
        bool isWord(const std::string& str);

        // take user input from terminal
        void inputState();

        // ask user for result
        void transitionState();

        // remove words from wordBank based on guess and result
        void workingState();

        // list possible words and make suggestions
        void suggestions();

        // find 3 best words to guess based on wordBank
        void bestWords();

        // private variables
        bool success;
        uint32_t attempts;
        std::string word_choice;
        std::string guess_result;
        std::vector<std::string> wordBank;
};


#endif //WORDLE_SOLVER_WORDLESOLVER_H
