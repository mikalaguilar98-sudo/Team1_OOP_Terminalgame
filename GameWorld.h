#ifndef GAMEWORLD_H
#define GAMEWORLD_H
#include "Entity.h"
#include "Player.h"
#include "Enemies.h"
#include <vector>
#include <mutex>
#include <chrono>

class Game;
class World;

class Game{//main game class to manage the world and game loop with threads, clock and the world class
    private:
        World& world; //game world, has players, enemies and their interactions
    public:
        Game(World& w);
        void startGame();
};

class World{
    private:
        Player player;
        std::vector<Enemy> enemies; //store multiple enemies
        int worldSizeX, worldSizeY; //size of the world, can be used to limit player and enemy movement
        std::vector<std::vector<int>> grid; //2D grid to represent the world
        std::mutex worldMutex; //protects enemies vector
        std::chrono::steady_clock::time_point lastTick; //track the last game tick
        std::chrono::milliseconds tickDuration{100}; //duration of each game tick (100ms)
    public:
        World(int sizeX, int sizeY, Player p);
        void addenemy(Enemy e);
        void movePlayer(int x, int y);
        void moveEnemies();
        //game loop, can be called in main to start the game for thread safety and tick management
        void gameLoop();

        //getters
        Player& getPlayer() {return player;}
        const std::vector<Enemy>& getEnemies() const { return enemies;}
        std::mutex& getMutex(){return worldMutex;} //getter for render thread
};

#endif //GAMEWORLD_H
