#include <iostream>
#include <thread>
#include "Player.h"
#include "Enemies.h"
#include "GameWorld.h"
#include "Render.h"

int main(){
    std::cout << "\n\n\n\n\n\t\t\tWelcome! Press 1 to Start: ";
    int i;
    if (!(std::cin >> i) || i != 1) return 0;
    //use char not string to make player
    Player player(10, 10, '@', 100, 0, 10, 11, 10);
    //set up world and game
    World world(80, 24, player);
    Game game(world);

    //spawn starting enemies
    world.addenemy(Enemy(20, 5, 'X', 30, 5));
    world.addenemy(Enemy(40, 10, 'X', 30, 5));

    //1 start logic thread in background
    std::thread logicThread([&]() {
        game.startGame();
    });
    //2 start UI on main thread (blocks until escape)
    startGameUI(world);

    //3 clean up
    if (logicThread.joinable()){
        logicThread.detach();
    }
    return 0;
}