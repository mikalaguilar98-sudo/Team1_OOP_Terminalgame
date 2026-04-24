#include <iostream>
#include <vector> //for managing multiple enemies
#include <mutex> //for thread safety when adding enemies
#include <chrono> //for managing game ticks
#include <algorithm> //for removing dead enemies
#include "Entity.h"
#include "Player.h"
#include "Enemies.h"
#include "GameWorld.h"

Game::Game(World& w) : world(w){//create game with a world and its player and enemies
        }
void Game::startGame(){
            while (true){ //game loop, can be exited with a condition like player health <= 0 or a certain score
                world.gameLoop(); //call game loop method from world to update positions and attacks based on ticks
                std::this_thread::sleep_for(std::chrono::milliseconds(10));//let CPU sleep so doesnt hit 100%
            }
        }

World::World(int sizeX, int sizeY, Player p) : player(p), worldSizeX(sizeX), worldSizeY(sizeY){ //dont need to pass enemies, they will be generated in the world
            //creat a 2D grid of correct size filled with 0s
            grid.resize(sizeY, std::vector<int>(sizeX, 0));
            //make world size
            lastTick = std::chrono::steady_clock::now();
        }
void World::addenemy(Enemy e){
            std::lock_guard<std::mutex> lock(worldMutex); //lock the mutex to protect the enemies vector while adding a new enemy
            enemies.push_back(e); //add enemy to the enemies vector
        }
void World::movePlayer(int x, int y){
            if (x >= 0 && x < worldSizeX && y >= 0 && y < worldSizeY){ //check if new position is inside the world boundaries
                player.move(x, y); //move player to new position
            }
        }
void World::moveEnemies(){
            std::lock_guard<std::mutex> lock(worldMutex); //lock the mutex to protect the enemies vector while moving enemies
            for (Enemy& enemy : enemies){
                enemy.moveToPlayer(player); //move each to the player
            }
        }
        //game loop, can be called in main to start the game for thread safety and tick management
void World::gameLoop(){
            auto now = std::chrono::steady_clock::now(); //get current time

            //only fun if 100ms passed
            if (now - lastTick >= tickDuration){
                //Lock: protect enemies and player while updating
                std::lock_guard<std::mutex> lock(worldMutex);
                // 1. Move enemies to player
                for(Enemy& enemy : enemies){
                    enemy.moveToPlayer(player);
                }
                // 2. Check for collisions and attacks
                for (Enemy& enemy : enemies){
                    enemy.attackPlayer(player); //enemies attack player if in same position
                    enemy.playerAttackEnemy(player); //player attacks enemy if in same position as weapon
                }
                // 3. remove dead enemies
                enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e){ return e.getHealthPoints() <= 0; }), enemies.end());
                // 4. update last tick time
                lastTick = now;
            }
        }

std::mutex& getMutex();
const std::vector<Enemy>& getEnemies();