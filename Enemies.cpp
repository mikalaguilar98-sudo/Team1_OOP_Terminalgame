#include <iostream>
#include <vector> //store enemies in a vector for easy management
#include "Entity.h"
#include "Player.h"
#include "Enemies.h"

Enemy::Enemy(int x, int y, char obj, int hp, int dmg) : Entity( x, y, obj, hp){
            damage = dmg;
        }
int Enemy::getDamage() const{
            return damage; //to show damage done to player
        }
void Enemy::moveToPlayer(const Player& player){
            int playerX = player.getX(); //find and assign playets position
            int playerY = player.getY();
            //move 1 unit towards player
            int nextX = getX() + (playerX > getX() ? 1 : (playerX < getX() ? -1 : 0));
            int nextY = getY() + (playerY > getY() ? 1 : (playerY < getY() ? -1 : 0));
            move(nextX, nextY); //move enemy to new position
        }
void Enemy::attackPlayer(Player& player){
            if (getX() == player.getX() && getY() == player.getY()){
                player.takeDamage(damage); //attack player and reduce hp
            }
        }
void Enemy::playerAttackEnemy(Player& player){
            if (getX() == player.getWeaponX() && getY() == player.getWeaponY()){
                takeDamage(player.getDamage()); //take damage from player attack
            }
        }
int Enemy::getHealthPoints() const { return Entity::getHealthPoints(); }