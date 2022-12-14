#include <maze-game.h>

class Map {
    public:
    Map(std::vector<int> layout);
    void draw();
    void updateCollision();
    void move(MoveDirection direction);
    std::vector<uint32_t>* getPixels();
    bool isAtGoal();
    bool isAtDeath();

    private:
    std::vector<uint32_t> pixels;
    std::vector<int> layout;
    std::vector<int> initialLayout;
    std::vector<int> collision;
    int playerPosition;
};