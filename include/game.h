#include <map.h>

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
    std::string getResourcesPath();
    void render();
    bool handleEvent(SDL_Event* e);
    void cleanup();
};