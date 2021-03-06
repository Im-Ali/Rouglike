#pragma once
#include "Character.h"

class Zombie : public Character {
private:
    int orderNumber;
public:
    Zombie(char c, Coordinate position);
    void Interact(MapObject *c);
    const char *GetName();
    ~Zombie();
};