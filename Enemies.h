#ifndef ENEMIES_H
#define ENEMIES_H
#include <vector> //store enemies in a vector for easy management
#include "Entity.h"

class Player;

class Enemy : public Entity{
    private:
        int damage;
    public:
        Enemy(int x, int y, char obj, int hp, int dmg);
        int getDamage() const;
        void moveToPlayer(const Player& player);
        void attackPlayer(Player& player);
        void playerAttackEnemy(Player& player);
        int getHealthPoints() const;
};
#endif //ENEMIES_H