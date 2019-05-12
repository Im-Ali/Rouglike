#pragma once
#include "Character.h"
class Dragon : public Character {
 private:
     int delay = 0;
 public:
  Dragon(char c, Coordinate position);
  void Interact(MapObject *c);
  const char *GetName();
  bool Fireball();
  bool CanThrowFireball();
  void TickDone();
  ~Dragon();
};
