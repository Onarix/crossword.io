#ifndef WORDS_GENERATOR_H
#define WORDS_GENERATOR_H

#include <algorithm>
#include <sqlite3.h>
#include <iostream>
#include <random>
#include <vector>

#define HORIZONTAL false
#define VERTICAL true

const char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

class WordsGenerator {
   private:
    std::random_device rd;
    std::uniform_int_distribution<int> dist;
    std::uniform_int_distribution<int> points;
    std::uniform_int_distribution<int> letters;
    std::vector<std::string> words;
    std::vector<int> used;


   public:
    WordsGenerator(int tab_size);
    ~WordsGenerator();
    std::string getRandomWord();
    sf::Vector2<int> getRandomPoint(int seed, bool orientation);
    char getRandomLetter();
};

/// @brief WordsGenerator class constructor
WordsGenerator::WordsGenerator(int tab_size) : dist(0, 999), points(0, tab_size - 1), letters(0, 25) {
    sqlite3_stmt *statement;
    sqlite3* wordDB;
    int return_code;


    return_code = sqlite3_open("data/words.db", &wordDB);
    if (return_code != SQLITE_OK) {
        std::cerr << "The database file containing words doesn't exist!\n";
    }

    const char *sql = "SELECT word FROM WORDS;";
    return_code = sqlite3_prepare_v2(wordDB, sql, -1, &statement, nullptr);
    if (return_code != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(wordDB) << std::endl;
        sqlite3_close(wordDB);
    }

    while ((return_code = sqlite3_step(statement)) == SQLITE_ROW) {
        const unsigned char *word = sqlite3_column_text(statement, 0);
        words.push_back(std::string(reinterpret_cast<const char*>(word)));
    }

    if (return_code != SQLITE_DONE) {
        std::cerr << "Error retrieving data: " << sqlite3_errmsg(wordDB) << std::endl;
    }

    sqlite3_finalize(statement);
    sqlite3_close(wordDB);
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
inline sf::Vector2<int> WordsGenerator::getRandomPoint(int seed = -1, bool orientation = HORIZONTAL) {
    if (seed == -1)
        return {points(rd), points(rd)};
    else {
        if(orientation == HORIZONTAL) {
            std::cout << "seed: " << seed << std::endl;
            std::uniform_int_distribution<int> offset(0, seed);
            return {offset(rd), points(rd)};
        }
        else if(orientation == VERTICAL) {
            std::cout << "seed: " << seed << std::endl;
            std::uniform_int_distribution<int> offset(0, seed);
            return {points(rd), offset(rd)};
        }
        else
            return {points(rd), points(rd)};
    }
}

/// @brief Get Random letter from hardcoded alphabet
/// @return random letter
inline char WordsGenerator::getRandomLetter() {
    int randID = letters(rd);
    return alphabet[randID];
}

#endif