#include "pch.h"
#include "Dragon.h"
#include "Config.h"


Dragon::Dragon(char c, Coordinate position) : Character(Config::CFG().dragonHP, Config::CFG().dragonAttack, c, position) {}

void Dragon::Interact(MapObject *c) {
    if (!c->isPrincess())
        this->Attack(c);
}

const char * Dragon::GetName() {
    return "Dragon";
}

bool Dragon::CanThrowFireball() {
    if (this->delay == 0)
        return true;
    return false;
}

bool Dragon::Fireball() {
    if (this->delay == 0) {
        this->delay = Config::CFG().dragonFireballDelay;
        return true;
    }
    return false;
}

void Dragon::TickDone() {
    if (this->delay > 0)
        this->delay -= 1;
}

Dragon::~Dragon() {}
