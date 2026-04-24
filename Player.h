#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Enemy;

class Player : public Entity{
    private: //what else can we add to the player?
        int score;
        int damage;
        int weaponX, weaponY; //position of weapon, can be used to determine if player can attack enemy
    public:
        Player(int x, int y, char obj, int hp, int s, int d, int wX, int wY);
        void Score(int points);
        int getScore() const;
        int getDamage() const;
        void setDamage(int dmg);
        void attackEnemy(Enemy& enemy);
        int getWeaponX() const;
        int getWeaponY() const;
        void move(int x, int y); //move weapon
};   

#endif //PLAYER_H
