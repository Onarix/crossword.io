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
        
        for(int i = 0; i < word.length(); i++) {
            tile[i][start_point.y].setLetter(word[i]);
        }
        return true;

    } else if (orientation == VERTICAL) {
        if (word.length() > (this->height - start_point.y))
            return false;

        for(int i = 0; i < word.length(); i++) {
            tile[start_point.x][i].setLetter(word[i]);
        }
        return true;
    }
    else
        return false;
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
            // TODO: assume the starting position (of the first tile) based on the size of the table
            tile[i][j].setPosition(250 + tile[i][j].getSize() * i, 150 + tile[i][j].getSize() * j);
            // std::cout << "Tile[" << i << "][" << j << "] text pos: (" << tile[i][j].getLetter().getPosition().x << "," << tile[i][j].getLetter().getPosition().y << ")" << "\n";
        }
    }

    // WordGenerator Test
    // TODO: a fully working generating system
    WordsGenerator wordsGenerator(width);
    bool success = false;
    do {
        success = this->insertWord(wordsGenerator.getRandomWord(), HORIZONTAL, wordsGenerator.getRandomPoint());
    }while(!(success));
    
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