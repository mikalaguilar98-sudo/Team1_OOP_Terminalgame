#ifndef ENTITY_H
#define ENTITY_H

class Entity{
    private:
        int positionX, positionY;
        char object;
        int healthPoints;
    public:
        Entity(int x, int y, char obj, int hp);
        void move(int x, int y); //setter of positions
        int getX() const;//getter of positionX
        int getY() const; //getter of positionY
        void takeDamage(int damage);
        int getHealthPoints() const;
};

#endif //ENTITY_H