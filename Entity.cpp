#include <iostream>
#include "Entity.h"

Entity::Entity(int x, int y, char obj, int hp){
            positionX = x;
            positionY = y;
            object = obj;
            healthPoints = hp;
    }

void Entity::move(int x, int y){ //setter of positions
            positionX = x;
            positionY = y;
        }

int Entity::getX() const{ //getter of positionX
            return positionX;
        }

int Entity::getY() const{ //getter of positionY
            return positionY;
        }

void Entity::takeDamage(int damage){
            if (healthPoints > 0){
                healthPoints -= damage;
                if (healthPoints <= 0){
                    healthPoints = 0;
                }
            }
        }
int Entity::getHealthPoints() const { return healthPoints; }