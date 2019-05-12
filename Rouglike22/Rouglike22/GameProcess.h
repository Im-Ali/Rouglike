#pragma once
#include "map.h"
#include "Character.h"
#include "Config.h" 

const int MAX_OBJECTS = 256;

class GameProcess {
 private:
     int width, height;
     WINDOW *win, *info;
     map *gameMap;
     MapObject *characters[MAX_OBJECTS];
     Config *config;
     void addProjectile(Coordinate coord, int direction, int damage, char c);
 public:
  GameProcess(Config *cfg);
  ~GameProcess();
};
