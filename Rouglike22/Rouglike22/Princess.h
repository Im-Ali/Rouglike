#pragma once
#include "Character.h"
class Princess : public Character {
public:
    Princess(char sym, Coordinate position);
    bool isPrincess();
    void Interact(MapObject *c);
    const char *GetName();
    void ReceiveDamage(int damage);
    ~Princess();
};
