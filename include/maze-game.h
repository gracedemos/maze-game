#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define RENDER_WIDTH 32
#define RENDER_HEIGHT 24

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