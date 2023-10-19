#include <iostream>

#include "Table.hpp"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define HORIZONTAL false
#define VERTICAL true

// Background
#define WHITE sf::Color(255, 255, 255)

// THIS IS A VERY ALPHA VERSION OF THE PROJECT!

int main() {
    // Window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "crossword.io");

    // Text
    sf::Font font;
    if (!font.loadFromFile("data/font.ttf"))
        return EXIT_FAILURE;
    sf::Text title("crossword.io", font, 24);
    title.setFillColor(sf::Color(0, 0, 0, 255));
    title.setPosition(40.f, 20.f);

    // Table
    Table table(10, 10, font);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // RENDER
        window.clear(WHITE);
        window.draw(title);
        window.draw(table);
        window.display();
    }

    return EXIT_SUCCESS;
}