#include "Game.hpp"

Game::Game() : isRunning(true), playerX(40), playerY(12) {
    map.resize(height, std::vector<char>(width, '.'));
}

void Game::run() {
    initialize();
    
    while (isRunning) {
        processInput();
        update();
        render();
    }
    
    std::cout << "\nGame Over! Thanks for playing.\n";
}

void Game::initialize() {
    std::cout << "========================================\n";
    std::cout << "      DUNGEON DELVER v0.1 (Console)     \n";
    std::cout << "========================================\n";
    std::cout << "Controls: WASD to move, Q to quit\n\n";
    
    generateMap();
    // Place player in center
    playerX = width / 2;
    playerY = height / 2;
    map[playerY][playerX] = '@';
}

void Game::processInput() {
    char input;
    std::cout << "Move (WASD) or Q to quit: ";
    std::cin >> input;
    
    switch(tolower(input)) {
        case 'w': movePlayer(0, -1); break;
        case 'a': movePlayer(-1, 0); break;
        case 's': movePlayer(0, 1); break;
        case 'd': movePlayer(1, 0); break;
        case 'q': isRunning = false; break;
        default: std::cout << "Invalid input!\n";
    }
}

void Game::update() {
    // For now, just update player position on map
    // Clear old position
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] == '@') {
                map[y][x] = '.';
            }
        }
    }
    // Set new position
    map[playerY][playerX] = '@';
}

void Game::render() {
    std::cout << "\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << map[y][x];
        }
        std::cout << "\n";
    }
    std::cout << "\nPlayer position: (" << playerX << ", " << playerY << ")\n";
}

void Game::generateMap() {
    // Simple map - walls around edges
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 0 || x == width-1 || y == 0 || y == height-1) {
                map[y][x] = '#';
            } else {
                map[y][x] = '.';
            }
        }
    }
    
    // Add some random walls inside
    srand(time(0));
    for (int i = 0; i < 50; i++) {
        int x = rand() % (width-2) + 1;
        int y = rand() % (height-2) + 1;
        map[y][x] = '#';
    }
}

void Game::movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;
    
    // Check bounds and walls
    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
        if (map[newY][newX] != '#') {
            playerX = newX;
            playerY = newY;
        } else {
            std::cout << "Can't move through walls!\n";
        }
    }
}