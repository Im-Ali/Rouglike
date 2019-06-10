#pragma once
#include "Character.h"
class Projectile : public Character {
private:
    int delay = 0;
    Direction savedDirection;
    MapObject *nonInteractedObject;
public:
    MapObject *GetNonInteractedObject();
    void ClearNonInteractedObject();
    Projectile(int damage, char sym, Coordinate pos, Direction direction);
    ~Projectile();
    void SetMoveDirection(Direction direction);
    const char *GetName();
    bool isProjectile();
    void Interact(MapObject *c);
    void TickDone();
};
