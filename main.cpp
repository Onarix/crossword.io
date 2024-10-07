#include <iostream>

#include "Table.hpp"
#include "Cursor.hpp"

// Background
#define WHITE sf::Color(255, 255, 255)

// Table size
#define SIZE 14

// THIS IS A VERY ALPHA VERSION OF THE PROJECT!

int main() {
    // Window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "crossword.io");
    window.setMouseCursorVisible(false);

    // Text
    sf::Font font;
    if (!font.loadFromFile("data/font.ttf"))
        return EXIT_FAILURE;
    sf::Text title("crossword.io", font, 24);
    title.setFillColor(sf::Color(0, 0, 0, 255));
    title.setPosition(40.f, 20.f);

    // Table
    Table table(SIZE, SIZE, font);
    int tile_x = 0;
    int tile_y = 0;
    int colored_x = 0;
    int colored_y = 0;
    int lineStart_x = 0;
    int lineStart_y = 0;

    // Cursor
    Cursor cursor;
    sf::Texture texture;
    texture.loadFromFile("data/cursor.png");
    sf::Sprite cursorSprite(texture);
    cursorSprite.setScale({0.1, 0.1});
    const sf::Vector2f mouse_offset = {0.f, 20.f};
    sf::Vector2f line_start = {0.f, 0.f};
    sf::Vector2f line_end = {0.f, 0.f};
    const sf::Vector2f line_offset = {21.f, 20.f};
    sf::Vector2i direction = {0, 0};
    bool isLeftButtonHeld = false;
    std::vector<sf::Vector2i> highlighted = {};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        tile_x = (sf::Mouse::getPosition().x - table.getStartPoint().x) / TILE_SIZE;
        tile_y = (sf::Mouse::getPosition().y - table.getStartPoint().y) / TILE_SIZE;
        
        // CURSOR
        if((tile_x != colored_x || tile_y != colored_y) && !(isLeftButtonHeld)) {   
            if(highlighted.size() > 1) {
                std::cout << "Word length: " << highlighted.size() << std::endl;
                for(auto elem : highlighted) {
                    table.setTileLetterColor(BLACK, elem.x, elem.y);
                }
                std::cout << "Direction: [" << direction.x << " , " << direction.y << "]\n"; 
            }
            table.setTileLetterColor(BLACK, colored_x, colored_y);
        
            highlighted.clear();
        }

        // Mark tile with color blue when cursor is over it
        if(tile_x >= 0 && tile_x < SIZE && tile_y >= 0 && tile_y < SIZE) {

            if(highlighted.size() == 1) {
                direction = {tile_x - colored_x, tile_y - colored_y};
            }
            
            if(!(isLeftButtonHeld)) {
                table.setTileLetterColor(BLUE, tile_x, tile_y);
            } else if(tile_x == lineStart_x || tile_y == lineStart_y) {
                if(highlighted.empty()
                    || (tile_x == highlighted.back().x + direction.x && direction.x != 0) 
                    || (tile_y == highlighted.back().y + direction.y && direction.y != 0)
                ) {
                    table.setTileLetterColor(BLUE, tile_x, tile_y);
                    highlighted.push_back(sf::Vector2i(tile_x, tile_y));
                }else if((tile_x == highlighted.back().x - direction.x && direction.x != 0)
                    || (tile_y == highlighted.back().y - direction.y && direction.y != 0)
                ) {
                    table.setTileLetterColor(BLACK, highlighted.back().x, highlighted.back().y);
                    highlighted.pop_back();
                }
                
                
            }
                
            colored_x = tile_x; colored_y = tile_y;
        }

        // Left click line mechanics
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if(!(isLeftButtonHeld)) {
                line_start = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) + line_offset;
                lineStart_x = tile_x;
                lineStart_y = tile_y;
                isLeftButtonHeld = true;
            }
            line_end = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) + line_offset;
            cursor.setLine(line_start, line_end);
        } else {
            isLeftButtonHeld = false;
            cursor.resetLine();
        }
    
        cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)) + mouse_offset);

        // RENDER
        window.clear(WHITE);
        window.draw(title);
        window.draw(table);
        if(isLeftButtonHeld)
            window.draw(cursor);
        window.draw(cursorSprite);
        window.display();
    }

    return EXIT_SUCCESS;
}