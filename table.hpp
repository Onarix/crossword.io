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
    sf::Vector2f start_point = {0, 0}; // top-left point of table
    sf::Vector2f end_point = {0, 0}; // bottom-right point of table
    Tile** tile = nullptr;
    sf::Font& font;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool insertWord(std::string word, bool orientation, sf::Vector2<int> start_point);
    void fillRestWithLetters();

   public:
    Table(int _width, int _height, sf::Font& _font);
    ~Table();
    Tile getTile(int x, int y);
    void setTileLetterColor(const sf::Color& color, int tile_x, int tile_y);
    sf::Vector2f getStartPoint();
    sf::Vector2f getEndPoint();
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

        std::cout << "Word length checked\n";

        for (int i = start_point.x; i < start_point.x + word.length(); i++) {
            if(tile[i][start_point.y].isOverwritten())
                return false;
        }

        std::cout << "Space checked\n";


        for (int i = start_point.x; i < start_point.x + word.length(); i++) {
            tile[i][start_point.y].setLetter(word[i - start_point.x]);
        }

        std::cout << "Word set checked\n";
    
        return true;

    } else if (orientation == VERTICAL) {
        if (word.length() > (this->height - start_point.y))
            return false;

        std::cout << "Word length checked\n";


        for (int i = start_point.y; i < start_point.y + word.length(); i++) {
            if(tile[start_point.x][i].isOverwritten()) {
                if(word[i - start_point.y] == tile[start_point.x][i].getLetter().getString()[0])
                    continue;
                return false;
            }
        }

        std::cout << "Space checked\n";

        for (int i = start_point.y; i < start_point.y + word.length(); i++) {
            tile[start_point.x][i].setLetter(word[i - start_point.y]);
        }

        std::cout << "Word set checked\n";

        return true;
    } else
        return false;
}

/// @brief Fills rest of the table with random letters
inline void Table::fillRestWithLetters() {
    WordsGenerator wordsGenerator(this->width);

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            if (!(tile[i][j].isOverwritten())) {
                tile[i][j].setLetter(wordsGenerator.getRandomLetter());
            }
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

    start_point.x = (SCREEN_WIDTH / 2) - ((TILE_SIZE * this->width) / 2);
    start_point.y = (SCREEN_HEIGHT / 2) - ((TILE_SIZE * this->height) / 2);
    end_point.x = start_point.x + (TILE_SIZE * this->width);
    end_point.y = start_point.y + (TILE_SIZE * this->height);

    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            tile[i][j].setPosition(start_point.x + tile[i][j].getSize() * i, start_point.y + tile[i][j].getSize() * j);
        }
    }

    // WordGenerator Test
    // TODO: a fully working generating system
    WordsGenerator wordsGenerator(this->width);
    int tries = 0;
    bool success = false;
    std::string word = "";
    sf::Vector2i point;

   std::cout << "HORIZONTAL\n";

   for(int i = 0; i < this->width / 4; i++) {
        word = wordsGenerator.getRandomWord();
        point = wordsGenerator.getRandomPoint(this->width - word.length(), HORIZONTAL);
        
        do {
            std::cout << ++tries << "try  - " << word << " ( " << point.x << "," << point.y << " )" << "\n";
            success = this->insertWord(word, HORIZONTAL, point);
            point.y = (point.y + 1) % this->width;
        } while (!(success));
   }

    std::cout << "VERTICAL\n";
   for(int i = 0; i < this->width / 4; i++) {
            word = wordsGenerator.getRandomWord();
            point = wordsGenerator.getRandomPoint(this->height - word.length(), VERTICAL);

        do {
            std::cout << ++tries << "try  - " << word << " ( " << point.x << "," << point.y << " )" << "\n";
            success = this->insertWord(word, VERTICAL, point);
            point.x = (point.x + 1) % this->width;
        } while (!(success));
   }

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

/// @brief Returns tile object on (x,y) position
/// @param x horizontal position of tile
/// @param y vertical position of tile
/// @return tile object
inline Tile Table::getTile(int x, int y) {
    return this->tile[x][y];
}

/// @brief Sets letter color of tile with specified coordinates 
/// @param color Color to be set
/// @param tile_x X-pos of tile
/// @param tile_y Y-pos of tile
inline void Table::setTileLetterColor(const sf::Color& color, int tile_x, int tile_y) {
    tile[tile_x][tile_y].setLetterColor(color);
}

/// @brief Returns starting point (left-top) of the table
/// @return start_point
inline sf::Vector2f Table::getStartPoint() {
    return this->start_point;
}

/// @brief Returns ending point (right-bottom) of the table
/// @return end_point
inline sf::Vector2f Table::getEndPoint() {
    return this->end_point;
}

#endif