#include <SDL.h>
#include <vector>
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

class Map {
    public:
    Map(std::vector<int> layout) {
        pixels.resize(RENDER_WIDTH * RENDER_HEIGHT);
        collision.resize(RENDER_WIDTH * RENDER_HEIGHT);
        this->layout = layout;

        for(int i = 0; i < layout.size(); i++) {
            if(layout[i] == MAP_PLAYER) {
                playerPosition = i;
            }
        }
    }
    void draw() {
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
    void updateCollision() {
        for(int i = 0; i < layout.size(); i++) {
            if(layout[i] == MAP_WALL) {
                collision[i] = 1;
            }else {
                collision[i] = 0;
            }
        }
    }
    void move(MoveDirection direction) {
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
    std::vector<uint32_t>* getPixels() {
        return &pixels;
    }

    private:
    std::vector<uint32_t> pixels;
    std::vector<int> layout;
    std::vector<int> collision;
    int playerPosition;
};

class Game {
    public:
    void run() {
        initSDL();
        mainLoop();
        cleanup();
    }

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Map* map;
    SDL_Texture* texture;

    void initSDL() {
        SDL_Init(SDL_INIT_VIDEO);

        window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_RenderSetLogicalSize(renderer, RENDER_WIDTH, RENDER_HEIGHT);

        std::vector<int> layout(RENDER_WIDTH * RENDER_HEIGHT);
        layout[0] = MAP_PLAYER;
        layout[40] = MAP_WALL;

        map = new Map(layout);

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);
    }
    void mainLoop() {
        bool quit = false;
        SDL_Event e;
        
        while(!quit) {
            quit = handleEvent(&e);
            render();
        }
    }
    void render() {
        map->draw();
        SDL_UpdateTexture(texture, nullptr, map->getPixels()->data(), RENDER_WIDTH * sizeof(uint32_t));
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
    bool handleEvent(SDL_Event* e) {
        bool ret = false;

        while(SDL_PollEvent(e) != 0) {
            if(e->type == SDL_QUIT) {
                ret = true;
            }else if(e->type == SDL_KEYDOWN) {
                switch(e->key.keysym.sym) {
                    case SDLK_d:
                        map->move(MOVE_RIGHT);
                        break;
                    case SDLK_a:
                        map->move(MOVE_LEFT);
                        break;
                    case SDLK_w:
                        map->move(MOVE_UP);
                        break;
                    case SDLK_s:
                        map->move(MOVE_DOWN);
                        break;
                }
            }
        }

        return ret;
    }
    void cleanup() {
        delete map;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }
};

int main(int argc, char** argv) {
    Game game;
    game.run();
    return 0;
}