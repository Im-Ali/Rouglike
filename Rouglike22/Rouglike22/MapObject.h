#pragma once

struct Coordinate {
  int x, y;
};

class MapObject {
 private:
     char sym;
 protected:
  Coordinate position;
  int hp, maxHP; 
 public:
  bool interactWithProjectile = true;
  bool canBeJumped = false;
  bool canMove = false;
  int GetHP();
  char GetSym();
  Coordinate GetPos();
  virtual void Interact(MapObject *c) = 0;
  virtual bool isPrincess();
  virtual bool isProjectile();
  virtual void ReceiveDamage(int damage);
  virtual void TickDone();
  virtual const char *GetName() = 0;
  void RestoreHP(int hp);
  MapObject(char sym, Coordinate pos);
  ~MapObject();
};
