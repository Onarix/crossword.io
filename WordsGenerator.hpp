#ifndef WORDS_GENERATOR_H
#define WORDS_GENERATOR_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

// NOTE: Let's leave MySQL for a while, temporarily working just o na plain .txt file

/*#include "C:/Program Files/MySQL/MySQL Server 8.0/include/mysql.h"  // Path to mySQL lib
#include "C:/Program Files/MySQL/Connector C++ 8.0/include/mysqlx/xapi.h"*/

char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

class WordsGenerator {
   private:
    std::random_device rd;
    std::uniform_int_distribution<int> dist;
    std::uniform_int_distribution<int> points;
    std::uniform_int_distribution<int> letters;
    std::vector<std::string> words;
    std::vector<int> used;
    std::fstream wordDB;

   public:
    WordsGenerator(int tab_size);
    ~WordsGenerator();
    std::string getRandomWord();
    sf::Vector2<int> getRandomPoint();
    char getRandomLetter();
};

/// @brief WordsGenerator class constructor
WordsGenerator::WordsGenerator(int tab_size) : dist(0, 999), points(0, tab_size), letters(0, 25) {
    wordDB.open("data/words.txt", std::ios::in);
    if (!(wordDB)) {
        std::cerr << "The file containing words doesn't exist!\n";
    }

    std::string temp = std::string();
    while (!(wordDB.eof())) {
        wordDB >> temp;
        words.push_back(temp);
    }

    wordDB.close();
}

/// @brief WordsGenerator class destructor
inline WordsGenerator::~WordsGenerator() {
}

/// @brief Get random word
/// @return random word
inline std::string WordsGenerator::getRandomWord() {
    int randIndex = dist(rd);
    std::string res = words[randIndex];
    if (std::find(used.begin(), used.end(), randIndex) != std::end(used)) {
        randIndex = dist(rd);
        res = words[randIndex];
    }
    used.push_back(randIndex);
    return res;
}

/// @brief Get random point in game table
/// @return random sf::Vector2 point
inline sf::Vector2<int> WordsGenerator::getRandomPoint() {
    return {points(rd), points(rd)};
}

/// @brief Get Random letter from hardcoded alphabet
/// @return random letter
inline char WordsGenerator::getRandomLetter() {
    int randID = letters(rd);
    return alphabet[randID];
}

#endif