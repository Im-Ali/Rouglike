#pragma once
#include "Character.h"
class Projectile : public Character {
 private:
     int delay = 0;
     int savedDirection;
     MapObject *nonInteractedObject;
 public:
  MapObject *GetNonInteractedObject();
  void ClearNonInteractedObject();
  Projectile(int damage, char sym, Coordinate pos, int direction);
  ~Projectile();
  void SetMoveDirection(int direction);
  const char *GetName();
  bool isProjectile();
  void Interact(MapObject *c);
  void TickDone();
};
