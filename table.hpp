#ifndef TABLE_H
#define TABLE_H

#include "SDL_SETUP.hpp"

#define TILE_SIZE 40  // width and height are the same - let's call them 'size'

class Table {
   private:
   public:
    // Width and height are measured in tiles (ex. xWidth = 5 means 5 tiles width)
    int width = 0;
    int height = 0;
    SDL_Rect** rect = nullptr;

    Table(int _xWidth, int _yWidth, SDL_Renderer* renderer);
    ~Table();
    SDL_Rect newSDL_Tile(int xs, int ys, int widths, int heights);
    void draw(SDL_Renderer* m_window_renderer, int width, int height);
};

/// @brief
/// @param _width
/// @param _height
/// @param renderer
inline Table::Table(int _width, int _height, SDL_Renderer* renderer) : width(_width), height(_height) {
    rect = new SDL_Rect*[width];
    for (int i = 0; i < width; i++) {
        rect[i] = new SDL_Rect[height];
    }
    std::cout << "Table initialized!\n";
}

/// @brief
inline Table::~Table() {
    for (int i = 0; i < width; i++) {
        delete[] rect[i];
    }
    delete[] rect;
    std::cout << "Table destroyed!\n";
}

/// @brief
/// @param xs
/// @param ys
/// @param widths
/// @param heights
/// @return
SDL_Rect Table::newSDL_Tile(int xs, int ys, int widths, int heights) {
    SDL_Rect rectangular;
    rectangular.x = xs;
    rectangular.y = ys;
    rectangular.w = widths;
    rectangular.h = heights;
    return rectangular;
}

/// @brief
/// @param m_window_renderer
/// @param width
/// @param height
inline void Table::draw(SDL_Renderer* m_window_renderer, int width, int height) {
    SDL_RenderClear(m_window_renderer);

    // tile color
    SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // TODO: assume the starting position (of the first tile) based on the size of the table
            rect[i][j] = newSDL_Tile(250 + 40 * i, 150 + 40 * j, TILE_SIZE, TILE_SIZE);
            SDL_RenderDrawRect(m_window_renderer, &rect[i][j]);
        }
    }

    SDL_RenderPresent(m_window_renderer);
}

#endif