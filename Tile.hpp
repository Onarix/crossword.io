#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define HORIZONTAL false
#define VERTICAL true

#define TILE_SIZE 60  // width and height are the same - let's call them 'size'
#define TILE_THICKNESS 4.f
#define LETTER_SIZE 40
#define LETTER_HEIGHT_OFFSET 5.f

// COLORS
#define BLACK sf::Color(0, 0, 0)
#define RED sf::Color(255, 0, 0)
#define GREEN sf::Color(0, 255, 0)
#define BLUE sf::Color(0, 255, 255)

/// @brief Tile class
class Tile : public sf::Drawable {
   private:
    sf::RectangleShape Body;
    sf::Text letter;
    bool overwriten;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   public:
    Tile();
    ~Tile();
    sf::RectangleShape getBody();
    sf::Text getLetter();
    sf::Color const getLetterColor() const;
    float getSize();
    void setLetterFont(sf::Font& font);
    void setLetter(char txt);
    void setLetterColor(const sf::Color& color);
    void setPosition(float x, float y);
    bool isOverwritten();
};

/// @brief Draws Tile object
/// @param target
/// @param states
inline void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->Body);
    target.draw(this->letter);
}

/// @brief Tile class constructor
inline Tile::Tile() {
    // BODY
    this->Body.setSize({TILE_SIZE, TILE_SIZE});
    this->Body.setOutlineColor(BLACK);
    this->Body.setOutlineThickness(TILE_THICKNESS);

    // TEXT
    this->letter.setString("");
    this->letter.setCharacterSize(LETTER_SIZE);
    this->letter.setFillColor(BLACK);

    // OVERWRITE SETUP
    this->overwriten = false;
}

/// @brief Tile class destructor
inline Tile::~Tile() {
}

/// @return Body (sf::RectangleShape) of Tile
inline sf::RectangleShape Tile::getBody() {
    return Body;
}

/// @return Letter (sf::Text) inside the Tile
inline sf::Text Tile::getLetter() {
    return letter;
}


/// @return Letter Color
inline const sf::Color Tile::getLetterColor() const {
    return this->letter.getFillColor();
}

/// @return Size of Tile
inline float Tile::getSize() {
    return TILE_SIZE;
}

/// @brief Sets the Tile letter font
/// @param font Reference to the font of program
inline void Tile::setLetterFont(sf::Font& font) {
    this->letter.setFont(font);
}

/// @brief Set letter in Tile
/// @param txt letter to be set
inline void Tile::setLetter(char txt) {
    std::string s(1, txt);
    this->letter.setString(s);
    this->overwriten = true;
}


/// @brief Sets letter color
/// @param color letter color to be set
inline void Tile::setLetterColor(const sf::Color& color) {
    this->letter.setFillColor(color);
}

/// @brief Sets the position of Tile
/// @param x x value of the position
/// @param y y value of the position
inline void Tile::setPosition(float x, float y) {
    this->Body.setPosition({x, y});
    this->letter.setPosition({x + float(TILE_SIZE / 4), y + float(TILE_SIZE / 4) - LETTER_HEIGHT_OFFSET});
}

/// @brief Check whether tile is overwritten by letter
/// @return True if the tile is overwritten, False otherwise
inline bool Tile::isOverwritten() {
    return this->overwriten;
}

#endif