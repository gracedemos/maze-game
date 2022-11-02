#include <map.h>

#ifdef __APPLE__
    #define WINDOW_FLAGS SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI
#elif _WIN64
    #define WINDOW_FLAGS SDL_WINDOW_SHOWN
#endif

class Game {
    public:
    void run();

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Map* map;
    SDL_Texture* texture;

    void initSDL();
    void mainLoop();
    std::vector<int> openLayout(std::string file);
    void render();
    bool handleEvent(SDL_Event* e);
    void cleanup();
};