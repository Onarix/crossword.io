#ifndef CURSOR_H
#define CURSOR_H

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>

#define LINE_THICKNESS 5.f

/// @brief Mouse cursor class
class Cursor : public sf::Drawable {
   private:
    sf::RectangleShape line;
    float length;
    float angle;
    sf::Vector2f direction;
   public:
    Cursor();
    ~Cursor(); 
    bool lineOver(float tileX, float tileY);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setLine(sf::Vector2f& start_point, sf::Vector2f& end_point);
    void resetLine();
};

/// @brief Cursor constructor
inline Cursor::Cursor() {
}

/// @brief Cursor destructor
inline Cursor::~Cursor() {
}


/// @brief Checks if line hovers over tile
/// @param tileX 
/// @param tileY 
/// @return Is line hovering over tile
bool Cursor::lineOver(float tileX, float tileY) {
    sf::FloatRect rect = this->line.getLocalBounds();
    return rect.contains(tileX, tileY);
}

/// @brief Draws line created by cursor
/// @param target 
/// @param states 
inline void Cursor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(line);
}

/// @brief Sets line drawn by cursor
/// @param start_point 
/// @param end_point 
inline void Cursor::setLine(sf::Vector2f& start_point, sf::Vector2f& end_point) {
    direction = end_point - start_point;
    length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159f; // To convert from radians to degrees
    line.setFillColor(BLACK);
    line.setSize(sf::Vector2f(length, LINE_THICKNESS));
    line.setRotation(angle);
    line.setPosition(start_point);
}

/// @brief Resets line drawn by cursor (makes it a (0,0) object on (0,0) position) 
inline void Cursor::resetLine() {
    line.setSize(sf::Vector2f(0,0));
    line.setPosition(sf::Vector2f(0,0));
}

#endif