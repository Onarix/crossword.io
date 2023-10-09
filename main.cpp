#include "SDL_SETUP.hpp"
#include "table.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// THIS IS A VERY FIRST, TEMPORARY VERSION OF THE PROJECT!
// TODO: class for every tile, that will consist of SDL_Rect shape and char inside it

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("crossword.io", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    Table tab(5, 5, renderer);

    bool running = true;
    bool game = false;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    game = true;
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (game)
            tab.draw(renderer, 5, 5);

        SDL_RenderPresent(renderer);
    }

    return 0;
}