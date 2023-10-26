#ifndef TABLE_H
#define TABLE_H

#include "Tile.hpp"
#include "WordsGenerator.hpp"

#define HORIZONTAL false
#define VERTICAL true

/// @brief Table that consists of Tiles
class Table : public sf::Drawable {
   private:
    // Width and height are measured in tiles (ex. xWidth = 5 means 5 tiles width)
    int width = 0;
    int height = 0;
    Tile** tile = nullptr;
    sf::Font& font;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool insertWord(std::string word, bool orientation, sf::Vector2<int> start_point);
    void fillRestWithLetters();

   public:
    Table(int _width, int _height, sf::Font& _font);
    ~Table();
};

/// @brief Draws Table Object
/// @param target
/// @param states
inline void Table::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            tile[i][j].setLetterFont(font);
            target.draw(tile[i][j]);
        }
    }
}

/// @brief Inserts a word into table
/// @param word word to be set
/// @param orientation HORIZONTAL(false) or VERTICAL(true)
/// @param start_point starting point of word
/// @return true, if the operation was successful and false in case of failure
inline bool Table::insertWord(std::string word, bool orientation, sf::Vector2<int> start_point) {
    if (orientation == HORIZONTAL) {
        if (word.length() > (this->width - start_point.x))
            return false;

        for (int i = start_point.x; i < word.length(); i++) {
            tile[i][start_point.y].setLetter(word[i]);
        }
        return true;

    } else if (orientation == VERTICAL) {
        if (word.length() > (this->height - start_point.y))
            return false;

        for (int i = start_point.y; i < word.length(); i++) {
            tile[start_point.x][i].setLetter(word[i]);
        }
        return true;
    } else
        return false;
}

/// @brief Fills rest of the table with random letters
inline void Table::fillRestWithLetters() {
    WordsGenerator wordsGenerator(this->width);
    // TODO: Work with this function, it only generates random letters at first row
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; i < this->height; i++) {
            if (!(tile[i][j].isOverwritten()))
                tile[i][j].setLetter(wordsGenerator.getRandomLetter());
        }
    }
}

/// @brief Table class constructor
/// @param _width table width (expressed in Tiles amount)
/// @param _height table height (expressed in Tiles amount)
/// @param font reference to the font used by program
inline Table::Table(int _width, int _height, sf::Font& _font) : width(_width), height(_height), font(_font) {
    tile = new Tile*[width];
    for (int i = 0; i < width; i++) {
        tile[i] = new Tile[height];
    }
    std::cout << "Table initialized!\n";

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            float x_start = (SCREEN_WIDTH / 2) - ((TILE_SIZE * this->width) / 2);
            float y_start = (SCREEN_HEIGHT / 2) - ((TILE_SIZE * this->height) / 2);
            tile[i][j].setPosition(x_start + tile[i][j].getSize() * i, y_start + tile[i][j].getSize() * j);
        }
    }

    // WordGenerator Test
    // TODO: a fully working generating system
    WordsGenerator wordsGenerator(this->width);
    bool success = false;
    do {
        success = this->insertWord(wordsGenerator.getRandomWord(), HORIZONTAL, wordsGenerator.getRandomPoint());
    } while (!(success));

    this->fillRestWithLetters();
}

/// @brief Table class destructor
inline Table::~Table() {
    for (int i = 0; i < width; i++) {
        delete[] tile[i];
    }
    delete[] tile;
    std::cout << "Table destroyed!\n";
}

#endif