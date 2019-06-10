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
#include "Config.h"

GameProcess::GameProcess() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();
    clear();
    srand(time(NULL));
    this->win = newwin(Config::CFG().mapHeight, Config::CFG().mapWidth, 0, 0);
    this->info = newwin(2, 20, 0, Config::CFG().mapWidth + 10);
    
    this->player = NULL;
    this->draco = NULL;
    this->princess = NULL;

    bool newGame = true;
    
    while (newGame) {
        if (this->InitMapAndCharacters()) {
            nodelay(this->win, true);
            GameResults result = GameResultNone;
            result = this->Run();
            
            this->ClearInput();
            nodelay(this->win, false);
            newGame = false;
            this->Clear();
            
            if (result != GameResultNone) {
                if (result == GameResultWin)
                    wprintw(this->win, "Вы выиграли");
                else if (result == GameResultDeadPrincess)
                    wprintw(this->win, "Вы не успели спасти принцессу - не все в жизни happy end");
                else if (result == GameResultLose)
                    wprintw(this->win, "Вы проиграли");
                wprintw(this->win, "\n\nХотите начать заново? (y/n)");
                
                char c = 'q';
                while (c != 'y' && c != 'n') {
                    c = wgetch(this->win);
                    if (c == 'y')
                        newGame = true;
                }
            }
        }
        else {
            wprintw(this->win, "Неверный формат карты: проверьте наличие игрока, принцессы и дракона");
            wgetch(this->win);
            
            this->Clear();
        }
    }
}

bool GameProcess::InitMapAndCharacters() {
    this->gameMap = new map(Config::CFG().mapWidth, Config::CFG().mapHeight);
    
    Coordinate position;
    const int MAX_OBJECTS = this->gameMap->width * this->gameMap->height;
    this->characters = new MapObject*[MAX_OBJECTS];
    // Инициализация персонажей
    for (int i = 0; i < MAX_OBJECTS; i++)
        this->characters[i] = NULL;
    int k1 = 1, k2 = MAX_OBJECTS - 3;
    // Генерация аптечек
    for (int i = 0; i < 3; i++) {
        position.x = (rand() % (this->gameMap->width - 2)) + 1;
        position.y = (rand() % (this->gameMap->height - 2)) + 1;
        this->characters[k1] = new Potion((rand() % (Config::CFG().potionValueMax - Config::CFG().potionValueMin + 1)) + Config::CFG().potionValueMin, Config::CFG().potionSym, position);
        k1++;
    }
    for (int i = 0; i < this->gameMap->height; i++) {
        for (int j = 0; j < this->gameMap->width; j++) {
            bool found = false; // true - символ найден на карте и его надо удалить
            position.x = j;
            position.y = i;
            char c = this->gameMap->data[i][j];
            if (c == Config::CFG().playerSym) {
                found = true;
                if (this->player == NULL)
                    this->player = new Knight(Config::CFG().playerHP, Config::CFG().playerAttack, c, position);
            }
            else if (c == Config::CFG().princessSym) {
                found = true;
                if (this->princess == NULL)
                    this->princess = new Princess(c, position);
            }
            else if (c == Config::CFG().dragonSym) {
                found = true;
                if (this->draco == NULL)
                    this->draco = new Dragon(c, position);
            }
            else if (c == Config::CFG().wallSym) {
                found = true;
                this->characters[k1] = new Wall(c, position);
                k1++;
            }
            else if (c == Config::CFG().zombieSym) {
                found = true;
                this->characters[k2] = new Zombie(c, position);
                k2--;
            }

            if (found)
                this->gameMap->data[i][j] = Config::CFG().mapDefaultSymbol;
        }
    }

    if (this->player == NULL || this->draco == NULL || this->princess == NULL) {
        return false;
    }
    else {
        this->characters[0] = this->player;
        this->characters[MAX_OBJECTS - 2] = this->draco;
        this->characters[MAX_OBJECTS - 1] = this->princess;
    }

    return true;
}

GameResults GameProcess::Run() {
    const int MAX_OBJECTS = this->gameMap->width * this->gameMap->height;
    Coordinate position;
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
        wrefresh(this->win);  // обновление экрана
        keypad(this->win, TRUE);
        
        char c = 0;
        bool move = false;
        MapObject *another = NULL;
        MapObject *currentObject = NULL;
        Character *current = NULL;
        Coordinate position2;
        bool win = false;
        int ticks = 0;
        Direction direction = DirectionRandom;
        while (c != 27) {
            ticks++;
            Log::WriteTicks(ticks);
            for (int i = 0; i < MAX_OBJECTS; i++) {
                if (this->characters[i] != NULL) this->characters[i]->TickDone();
            }
            
            Sleep(Config::CFG().gameDelay);
            c = wgetch(this->win);
            this->ClearInput();
            
            // обработка нажатой клавиши
            player->SetMoveDirection(PressButton(c, &direction));
            if (direction != DirectionNone) {
                // получить новую позицию исходя из направления
                position2 = NewCoordinate(player->GetPos(), direction);
                if (this->gameMap->isValidCoordinates(position2.x, position2.y) && player->ShootArrow())
                    this->addProjectile(position2, direction, Config::CFG().playerShootingAttack, Config::CFG().playerShootingSym);
            }

            // дракон плюет фаербол
            if (draco->CanThrowFireball()) {
                direction = Direction((rand() % 4) + 1);
                position2 = NewCoordinate(draco->GetPos(), direction);
                if (this->gameMap->isValidCoordinates(position2.x, position2.y) && draco->Fireball())
                    this->addProjectile(position2, direction, Config::CFG().dragonFireballAttack, Config::CFG().dragonFireballSym);
            }

            // обработка перемещений и столкновений
            for (int k = 0; k < MAX_OBJECTS; k++) {
                currentObject = this->characters[k];
                if (currentObject != NULL && currentObject->canMove) {
                    current = (Character *)currentObject;
                    move = false;
                    if (current->GetMoveDirection() == DirectionRandom)
                        current->SetMoveDirection(Direction((rand() % 4) + 1));
                    position = NewCoordinate(current->GetPos(), current->GetMoveDirection());
                    if (current->GetMoveDirection() != DirectionNone)
                        move = true;
                    Log::WriteMove(current, move);
                    current->SetMoveDirection(DirectionRandom);
                    
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
                                    if (current->GetHP() <= 0) {
                                        this->characters[k] = NULL;
                                        Coordinate old_position = current->GetPos();
                                        wmove(this->win, old_position.y, old_position.x);
                                        wprintw(this->win, "%c", this->gameMap->data[old_position.y][old_position.x]);
                                        delete current;
                                        current = NULL;
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
            
            if (win) {
                // выиграли
                return GameResultWin;
            }
            if (player->GetHP() <= 0) {
                // конец игры, hp не осталоесь
                return GameResultLose;
            }
            /*
            bool hasPrincess = false;
            for (int i = 0; i < MAX_OBJECTS; i++) {
                if (this->characters[i] != NULL && this->characters[i]->isPrincess()) {
                    hasPrincess = true;
                    break;
                }
            }
            */
            if (!this->princess) {
                // конец игры, принцессу убили
                return GameResultDeadPrincess;
            }
        }
    }
    return GameResultNone;
}

void GameProcess::addProjectile(Coordinate coord, Direction direction, int damage, char c) {
    int j = 0;
    while (this->characters[j] != NULL)
        j++;
    this->characters[j] = new Projectile(damage, c, coord, direction);
}

Direction GameProcess::PressButton(char c, Direction *projectileDirection) {
    Direction d = DirectionNone;
    *projectileDirection = DirectionNone;

    if (c == 'i' || c == 'I')
        *projectileDirection = DirectionUp;
    else if (c == 'j' || c == 'J')
        *projectileDirection = DirectionLeft;
    else if (c == 'k' || c == 'K')
        *projectileDirection = DirectionDown;
    else if (c == 'l' || c == 'L')
        *projectileDirection = DirectionRight;
    else if (c == 'a' || c == 'A')
        d = DirectionLeft;
    else if (c == 'd' || c == 'D')
        d = DirectionRight;
    else if (c == 'w' || c == 'W')
        d = DirectionUp;
    else if (c == 's' || c == 'S')
        d = DirectionDown;

    return d;
}

Coordinate GameProcess::NewCoordinate(Coordinate position, Direction direction) {
    Coordinate newPosition = position;

    if (direction == DirectionLeft)
        newPosition.x -= 1;
    else if (direction == DirectionRight)
        newPosition.x += 1;
    else if (direction == DirectionUp)
        newPosition.y -= 1;
    else if (direction == DirectionDown)
        newPosition.y += 1;

    return newPosition;
}

void GameProcess::ClearInput() {
    // очистить очередь нажатых клавиш в консоли
    while (wgetch(this->win) != ERR) flushinp();
}

void GameProcess::Clear() {
    if (this->characters) {
        for (int i = 0; i < this->gameMap->width * this->gameMap->height; i++)
            if (this->characters[i] != NULL)
                delete this->characters[i];
        delete this->characters;
    }
    this->player = NULL;
    this->draco = NULL;
    this->princess = NULL;

    if (this->gameMap)
        delete this->gameMap;

    wclear(this->info);
    wrefresh(this->info);
    wclear(this->win);
    wrefresh(this->win);
}

GameProcess::~GameProcess() {
    delwin(this->win);
    delwin(this->info);
}
