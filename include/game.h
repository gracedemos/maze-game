#include <map.h>

class Game {
    public:
    void run();

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Map* map;
    SDL_Texture* texture;
    int currentLevel;

    void initSDL();
    void mainLoop();
    void loadLevel(int num);
    std::vector<int> openLayout(std::string file);
    std::string getResourcesPath();
    void render();
    bool handleEvent(SDL_Event* e);
    void cleanup();
};