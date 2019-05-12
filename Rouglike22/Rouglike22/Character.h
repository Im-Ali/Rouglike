#pragma once
#include "MapObject.h"
 
 class Character : public MapObject {
 private:
     int damage;
 protected:
     int moveDirection; // 0 - стоит, 1 - влево, 2 - вправо, 3 - вверх, 4 - вниз
     int mana;
 public:
     int GetMP();
     int GetDamage();
     void MoveTo(Coordinate position);
     void Attack(MapObject *c);
     int GetMoveDirection();
     virtual void SetMoveDirection(int direction);
    
  Character(int hp, int damage, char sym, Coordinate pos);
  ~Character();
};
