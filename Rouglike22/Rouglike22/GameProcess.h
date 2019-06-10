#pragma once
#include "map.h"
#include "Knight.h"
#include "Dragon.h"
#include "Princess.h" 

enum GameResults {
    GameResultNone,
    GameResultWin,
    GameResultLose,
    GameResultDeadPrincess
};

class GameProcess {
private:
     int width, height;
     WINDOW *win, *info;
     
     map *gameMap;
     MapObject **characters;
     
     Knight *player;
     Dragon *draco;
     Princess *princess;

     void addProjectile(Coordinate coord, Direction direction, int damage, char c);
     Direction PressButton(char c, Direction *projectileDirection);
     Coordinate NewCoordinate(Coordinate position, Direction direction);

     bool InitMapAndCharacters();
     GameResults Run();

     void ClearInput();
     void Clear();
public:
    GameProcess();
    ~GameProcess();
};
