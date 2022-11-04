#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#ifdef __APPLE__
    #include <mach-o/dyld.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RENDER_WIDTH 32
#define RENDER_HEIGHT 24

#ifdef __APPLE__
    #define WINDOW_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
#elif _WIN64
    #define WINDOW_FLAGS SDL_WINDOW_SHOWN
#endif



enum MapElement {
    MAP_EMPTY,
    MAP_PLAYER,
    MAP_WALL
};

enum MoveDirection {
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN
};