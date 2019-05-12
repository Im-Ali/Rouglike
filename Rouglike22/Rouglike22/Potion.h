#pragma once
#include "MapObject.h"
class Potion : public MapObject {
 private:
     int upHP;
 public:
  Potion(int hp, char sym, Coordinate coord);
  void Interact(MapObject *c);
  const char *GetName();
  ~Potion();
};
