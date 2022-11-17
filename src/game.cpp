#include <game.h>

void Game::run() {
    initSDL();
    mainLoop();
    cleanup();
}

void Game::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderSetLogicalSize(renderer, RENDER_WIDTH, RENDER_HEIGHT);

    texture = nullptr;
    loadLevel(1);
}

void Game::loadLevel(int num) {
    SDL_DestroyTexture(texture);
    
    std::vector<int> layout = openLayout(getResourcesPath() + "/level-" + std::to_string(num) + ".bin");
    map = new Map(layout);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);
    currentLevel = num;
}

void Game::mainLoop() {
    bool quit = false;
    SDL_Event e;
    
    while(!quit) {
        if(map->isAtGoal()) {
            loadLevel(currentLevel + 1);
        }
        if(map->isAtDeath()) {
            loadLevel(1);
        }

        quit = handleEvent(&e);
        render();
    }
}

std::string Game::getResourcesPath() {
    #ifdef __APPLE__
        char path[1024];
        uint32_t size = sizeof(path);
        _NSGetExecutablePath(path, &size);
        std::string ret(path);
        return ret.substr(0, ret.size() - 10) + "/resources";
    #elif _WIN64
        return std::string("resources");
    #elif linux
        char path[1024];
        readlink("/proc/self/exe", path, 1024);
        return std::string(dirname(path)) + "/resources";
    #endif
}

std::vector<int> Game::openLayout(std::string path) {
    std::vector<char> buffer(768);

    std::ifstream file(path.c_str(), std::ios::binary);

    file.read(buffer.data(), 768);
    file.close();
    std::vector<int> layout(buffer.size());

    for(int i = 0; i < buffer.size(); i++) {
        layout[i] = buffer[i];
    }
    return layout;
}

void Game::render() {
    map->draw();
    SDL_UpdateTexture(texture, nullptr, map->getPixels()->data(), RENDER_WIDTH * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

bool Game::handleEvent(SDL_Event* e) {
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

void Game::cleanup() {
    delete map;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}