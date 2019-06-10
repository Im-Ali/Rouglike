#pragma once
#include "Character.h"
class Wall : public Character {
public:
    Wall(char sym, Coordinate position);
    void Interact(MapObject *c);
    void ReceiveDamage(int damage);
    const char *GetName();
    ~Wall();
};
