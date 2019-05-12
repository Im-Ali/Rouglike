#pragma once
#include "Character.h"
class Knight : public Character {
 private:
     int delay = 0;
     int manaRestoreDelay = 0;
     int maxMana;
 public:
     void Interact(MapObject *c);
  Knight(int hp, int damage, char sym, Coordinate pos);
  bool ShootArrow();
  void TickDone();
  const char *GetName();
  ~Knight();
};
