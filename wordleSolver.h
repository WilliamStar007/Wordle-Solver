#ifndef WORDLE_SOLVER_WORDLESOLVER_H
#define WORDLE_SOLVER_WORDLESOLVER_H

#include <string>
#include <set>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

// wordle solver class
class WordleSolver {
    public:
        // class constructor
        explicit WordleSolver(const std::string& filename);

        // attempt to solve wordle
        // return whether solved successfully
        bool solve();

        // return number of remaining attempts
        int getAttempts() { return attempts; }

    private:
        // load wordBank from file
        void loadFromFile(const std::string &fileName);

        // transforms input string to lower case
        // check if a string is a word from wordBank
        bool isWord(std::string& str);

        // transforms input string to upper case
        // check if a string is a valid result for a guess
        bool isResult(std::string& res);

        // take user input from terminal
        void inputState();

        // ask user for result
        void transitionState();

        // remove words from wordBank based on guess and result
        void workingState();

        // list possible words and make suggestions
        void suggestions();

        // find the best words to guess based on wordBank
        void bestWords();

        // private variables
        bool success;
        int attempts;
        std::string bestWord;
        std::string wordChoice;
        std::string guessResult;
        std::set<std::string> wordBank;
};


#endif //WORDLE_SOLVER_WORDLESOLVER_H
