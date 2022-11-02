#include <map.h>

Map::Map(std::vector<int> layout) {
    pixels.resize(RENDER_WIDTH * RENDER_HEIGHT);
    collision.resize(RENDER_WIDTH * RENDER_HEIGHT);
    this->layout = layout;

    for(int i = 0; i < layout.size(); i++) {
        if(layout[i] == MAP_PLAYER) {
            playerPosition = i;
        }
    }
}

void Map::draw() {
    for(int i = 0; i < layout.size(); i++) {
        switch(layout[i]) {
            case MAP_EMPTY:
                pixels[i] = 0x000000ff;
                break;
            case MAP_PLAYER:
                pixels[i] = 0xff0000ff;
                break;
            case MAP_WALL:
                pixels[i] = 0xffffffff;
        }
    }
}

void Map::updateCollision() {
    for(int i = 0; i < layout.size(); i++) {
        if(layout[i] == MAP_WALL) {
            collision[i] = 1;
        }else {
            collision[i] = 0;
        }
    }
}

void Map::move(MoveDirection direction) {
    switch(direction) {
        case MOVE_RIGHT:
            if(playerPosition + 1 < 768 && collision[playerPosition + 1] == 0) {
                layout[playerPosition] = MAP_EMPTY;
                playerPosition++;
                layout[playerPosition] = MAP_PLAYER;
            }
            break;
        case MOVE_LEFT:
            if(playerPosition - 1 >= 0 && collision[playerPosition - 1] == 0 ) {
                layout[playerPosition] = MAP_EMPTY;
                playerPosition--;
                layout[playerPosition] = MAP_PLAYER;
            }
            break;
        case MOVE_UP:
            if(playerPosition - RENDER_WIDTH >= 0 && collision[playerPosition - RENDER_WIDTH] == 0) {
                layout[playerPosition] = MAP_EMPTY;
                playerPosition -= RENDER_WIDTH;
                layout[playerPosition] = MAP_PLAYER;
            }
            break;
        case MOVE_DOWN:
            if(playerPosition + RENDER_WIDTH < 768 && collision[playerPosition + RENDER_WIDTH] == 0) {
                layout[playerPosition] = MAP_EMPTY;
                playerPosition += RENDER_WIDTH;
                layout[playerPosition] = MAP_PLAYER;
            }
            break;
    }
    updateCollision();
}

std::vector<uint32_t>* Map::getPixels() {
    return &pixels;
}