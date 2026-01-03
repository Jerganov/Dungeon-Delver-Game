#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>

class Game {
public:
    Game();
    void run();
    
private:
    bool isRunning;
    int playerX, playerY;
    const int width = 80;
    const int height = 24;
    std::vector<std::vector<char>> map;
    
    void initialize();
    void processInput();
    void update();
    void render();
    void generateMap();
    void movePlayer(int dx, int dy);
};

#endif