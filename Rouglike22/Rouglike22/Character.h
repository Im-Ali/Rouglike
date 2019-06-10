#pragma once
#include "MapObject.h"

enum Direction {
    DirectionRandom,
    DirectionLeft,
    DirectionRight,
    DirectionUp,
    DirectionDown,
    DirectionNone
};

 class Character : public MapObject {
 private:
     int damage;
 protected:
     Direction moveDirection;
     int mana;
 public:
     int GetMP();
     int GetDamage();
     void MoveTo(Coordinate position);
     void Attack(MapObject *c);
     Direction GetMoveDirection();
     virtual void SetMoveDirection(Direction direction);
    
     Character(int hp, int damage, char sym, Coordinate pos);
     ~Character();
};
