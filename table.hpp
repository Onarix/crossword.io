#ifndef TABLE_H
#define TABLE_H

#include "Tile.hpp"

/// @brief Table that consists of Tiles
class Table : public sf::Drawable {
   private:
    // Width and height are measured in tiles (ex. xWidth = 5 means 5 tiles width)
    int width = 0;
    int height = 0;
    Tile** tile = nullptr;
    sf::Font& font;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   public:
    Table(int _xWidth, int _yWidth, sf::Font& _font);
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