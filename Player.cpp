

#include <iostream>
#include "Entity.h"
#include "Player.h"
#include "Enemies.h"

Player::Player(int x, int y, char obj, int hp, int s, int d, int wX, int wY) : Entity(x, y, obj, hp){
            score = s;
            damage = d;
            weaponX = wX;
            weaponY = wY;
        }
void Player::Score(int points){
            score += points;
        }
int Player::getScore() const{
            return score;
        }
int Player::getDamage() const{
            return damage;
        }
void Player::setDamage(int dmg){
            damage = dmg;
        }
void Player::attackEnemy(Enemy& enemy){
            if (weaponX == enemy.getX() && weaponY == enemy.getY()){
                enemy.takeDamage(damage); //attack enemy and reduce hp
            }
        }
int Player::getWeaponX() const{
            return weaponX;
        }
int Player::getWeaponY() const{
            return weaponY;
        }

void Player::move(int x, int y){
    Entity::move(x, y); //move player to new position
    //update weapon position 1 unit in front
    weaponX = x + 1;
    weaponY = y;
}
