#include "pch.h"
#include <curses.h>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>
#include "GameProcess.h"
#include "Knight.h"
#include "Zombie.h"
#include "Dragon.h"
#include "Princess.h"
#include "Wall.h"
#include "Config.h"
#include "Projectile.h"
#include "Potion.h"
#include "Log.h"

GameProcess::GameProcess(Config *cfg) {
    this->config = cfg;
    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();
    clear();
    srand(time(NULL));
    this->gameMap = new map();
    this->win = newwin(this->gameMap->height, this->gameMap->width, 0, 0);
    this->info = newwin(2, 20, 0, this->gameMap->width + 10);
    
    nodelay(this->win, true);
    
    Coordinate position;
    
    for (int i = 0; i < MAX_OBJECTS; i++)
        characters[i] = NULL;

    position.x = 15;
    position.y = 1;
    Knight *player = new Knight(100, 25, this->config->playerSym, position);
    this->characters[0] = player;
    position.x = 3;
    position.y = 2;
    this->characters[MAX_OBJECTS - 4] = new Zombie(position);
    position.x = 19;
    position.y = 3;
    this->characters[MAX_OBJECTS - 3] = new Zombie(position);
    position.x = 6;
    position.y = 5;
    Dragon *draco = new Dragon(this->config->dragonSym, position);
    this->characters[MAX_OBJECTS - 2] = draco;
    position.x = 13;
    this->characters[MAX_OBJECTS - 1] = new Princess(position);
    position.x = 0;
    position.y = 0;
    int j = 1;
    // стенки
    while (position.x < this->gameMap->width - 1) {
        position.x++;
        this->characters[j] = new Wall(position);
        j++;
    }
    while (position.y < this->gameMap->height - 1) {
        position.y++;
        this->characters[j] = new Wall(position);
        j++;
    }
    while (position.x > 0) {
        position.x--;
        this->characters[j] = new Wall(position);
        j++;
    }
    while (position.y > 0) {
        position.y--;
        this->characters[j] = new Wall(position);
        j++;
    }
    // аптечки
    for (int i = 0; i < 3; i++) {
        position.x = (rand() % this->gameMap->width - 2) + 1;
        position.y = (rand() % this->gameMap->height - 2) + 1;
        this->characters[j] = new Potion((rand() % 31) + 20 /* 20-50 */, 'A', position);
        j++;
    }
  /*
  position.x = 15;
  position.y = 0;
  this->characters[10] = new Projectile(10, '*', position, 1);
  */

  if (this->win != nullptr) {
    // вывод карты
      for (int i = 0; i < this->gameMap->height; i++) {
        wmove(this->win, i, 0);
        for (int j = 0; j < this->gameMap->width; j++) {
          wprintw(this->win, "%c", this->gameMap->data[i][j]);
        }
      }
    // вывод персонажей
      for (int i = 0; i < MAX_OBJECTS; i++) {
          MapObject *c = this->characters[i];
          if (c != NULL) {
              position = c->GetPos();
              wmove(this->win, position.y, position.x);
              wprintw(this->win, "%c", c->GetSym());
          }
      }
  
    wrefresh(this->win); // обновление экрана
    
    keypad(this->win, TRUE);

    char c = 0;
    bool move = false;
    MapObject *another = NULL;
    MapObject *currentObject = NULL;
    Character *current = NULL;
    Coordinate position2;
    bool win = false;
    int ticks = 0;
    int direction = 0;
    while (c != 27) {
        ticks++;
        Log::WriteTicks(ticks);
        for (int i = 0; i < MAX_OBJECTS; i++) {
            if (this->characters[i] != NULL) 
                this->characters[i]->TickDone();
        }

        Sleep(200);
        c = wgetch(this->win);
        // очистить очередь в консоли
        while (wgetch(this->win) != ERR)
            flushinp();

        player->SetMoveDirection(0);
        position2 = player->GetPos();
        if (c == 'i' || c == 'I') {
            position2.y -= 1;
            if (this->gameMap->isValidCoordinates(position2.x, position2.y) && player->ShootArrow()) {
                this->addProjectile(position2, 3, 10, '+');
            }
            player->SetMoveDirection(5);
        }
        else if (c == 'j' || c == 'J') {
            position2.x -= 1;
            if (this->gameMap->isValidCoordinates(position2.x, position2.y) && player->ShootArrow()) {
                this->addProjectile(position2, 1, 10, '+');
            }
            player->SetMoveDirection(5);
        } 
        else if (c == 'k' || c == 'K') {
            position2.y += 1;
            if (this->gameMap->isValidCoordinates(position2.x, position2.y) && player->ShootArrow()) {
                this->addProjectile(position2, 4, 10, '+');
            }
            player->SetMoveDirection(5);
        }
        else if (c == 'l' || c == 'L') {
            position2.x += 1;
            if (this->gameMap->isValidCoordinates(position2.x, position2.y) && player->ShootArrow()) {
                this->addProjectile(position2, 2, 10, '+');
            }
            player->SetMoveDirection(5);
        } else if (c == 'a' || c == 'A') {
            // 1 - влево
            player->SetMoveDirection(1);
            //position.x -= 1;
            //move = true;
        }
        else if (c == 'd' || c == 'D') {
            // 2 - вправо
          player->SetMoveDirection(2);
            //position.x += 1;
            //move = true;
        }
        else if (c == 'w' || c == 'W') {
            // 3 - вверх
            player->SetMoveDirection(3);
            //position.y -= 1;
            //move = true;
        }
        else if (c == 's' || c == 'S') {
            // 4 - вниз
            player->SetMoveDirection(4);
            //position.y += 1;
            //move = true;
        } else
            player->SetMoveDirection(5);

        if (draco->CanThrowFireball()) {
            position2 = draco->GetPos();
            direction = (rand() % 4) + 1;
            if (direction == 1)
                position2.x -=1;
            else if (direction == 2)
                position2.x += 1;
            else if (direction == 3)
                position2.y -= 1;
            else
                position2.y += 1;
            if (this->gameMap->isValidCoordinates(position.x, position.y) && draco->Fireball())
                this->addProjectile(position2, direction, 40, '*');
        }

        for (int k = 0; k < MAX_OBJECTS; k++) {
            currentObject = this->characters[k];
            if (currentObject != NULL && currentObject->canMove) {
                current = (Character *) currentObject;
                move = false;
                position = current->GetPos();
                if (current->GetMoveDirection() == 0) {
                    current->SetMoveDirection((rand() % 4) + 1);
                }
                if (current->GetMoveDirection() == 1) {
                    position.x -= 1;
                    move = true;
                } 
                else if (current->GetMoveDirection() == 2) {
                    position.x += 1;
                    move = true;
                } 
                else if (current->GetMoveDirection() == 3) {
                    position.y -= 1;
                    move = true;
                }
                else if (current->GetMoveDirection() == 4) {
                    position.y += 1;
                    move = true;
                }
                Log::WriteMove(current, move);
                current->SetMoveDirection(0);

                if (move == true && !this->gameMap->isValidCoordinates(position.x, position.y)) {
                    move = false;
                    
                }
                if (move) {
                    for (int i = 0; i < MAX_OBJECTS; i++) {
                        another = this->characters[i];
                        if (another != NULL) {
                            position2 = another->GetPos();
                            if (another != current && position.x == position2.x && position.y == position2.y) {
                                if (current == player && another->isPrincess()) {
                                    win = true;
                                }
                                current->Interact(another);
                                another->Interact(current);
                                Log::WriteInteraction(current, another);
                                move = false;

                                if (another->GetHP() <= 0) {
                                    this->characters[i] = NULL;
                                    Coordinate old_position = another->GetPos();
                                    wmove(this->win, old_position.y, old_position.x);
                                    wprintw(this->win, "%c", this->gameMap->data[old_position.y][old_position.x]);
                                    delete another;
                                }
                                else if (current->GetHP() <= 0) {
                                    this->characters[k] = NULL;
                                    Coordinate old_position = current->GetPos();
                                    wmove(this->win, old_position.y, old_position.x);
                                    wprintw(this->win, "%c", this->gameMap->data[old_position.y][old_position.x]);
                                    delete current;
                                }
                                move = another->canBeJumped;
                                break;
                            }
                        }
                    }
                }
                
                if (current != NULL && move) {
                    Coordinate old_position = current->GetPos();
                    wmove(this->win, old_position.y, old_position.x);
                    wprintw(this->win, "%c", this->gameMap->data[old_position.y][old_position.x]);
                    
                    wmove(this->win, position.y, position.x);
                    wprintw(this->win, "%c", current->GetSym());
                    current->MoveTo(position);
                    
                    if (current->isProjectile()) {
                        Projectile *p = (Projectile *)current;
                        if (p->GetNonInteractedObject() != NULL) {
                            position = p->GetNonInteractedObject()->GetPos();
                            wmove(this->win, position.y, position.x);
                            wprintw(this->win, "%c", p->GetNonInteractedObject()->GetSym());
                            p->ClearNonInteractedObject();
                        }
                    }
                }
            }
        }
        
        wrefresh(this->win);

        wmove(this->info, 0, 0);
        wprintw(this->info, "HP: %3d\nMP: %3d", player->GetHP(), player->GetMP());
        wrefresh(this->info);
        
        if (win) break; // выиграли
        if (player->GetHP() <= 0) break;  // конец игры, hp не осталоесь
        bool hasPrincess = false;
        for (int i = 0; i < MAX_OBJECTS; i++) {
            if (this->characters[i] != NULL && this->characters[i]->isPrincess()) {
                hasPrincess = true;
                break;
            }
        }
        if (!hasPrincess)
            break; // конец игры, принцессу убили
    }
  }
}

void GameProcess::addProjectile(Coordinate coord, int direction, int damage, char c) {
    int j = 0;
    while (this->characters[j] != NULL)
        j++;
    this->characters[j] = new Projectile(damage, c, coord, direction);
}

GameProcess::~GameProcess() {
  for (int i = 0; i < MAX_OBJECTS; i++)
        if (this->characters[i] != NULL)
            delete this->characters[i];
  delete this->gameMap;
  delwin(this->win);
  delete this->config;
}
