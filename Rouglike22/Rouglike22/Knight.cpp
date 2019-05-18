#include "pch.h"
#include "Knight.h"

Knight::Knight(int hp, int damage, char sym, Coordinate pos) : Character(hp, damage, sym, pos)
{
    this->maxMana = 100;
    this->mana = this->maxMana;
}

void Knight::Interact(MapObject *c) {
    if (!c->isPrincess()) {
        this->Attack(c);
    }
}

const char *Knight::GetName() {
    return "Knight";
}

bool Knight::ShootArrow() {
    if (this->mana >= 5 && this->delay == 0) {
        this->mana -= 5;
        this->delay = 5;
        return true;
    }
    return false;
}

void Knight::TickDone() {
    if (this->delay > 0)
        this->delay -= 1;
    if (this->mana < this->maxMana) {
        if (this->manaRestoreDelay > 0)
            this->manaRestoreDelay -= 1;
        else {
            this->mana += 1;
            this->manaRestoreDelay = 7;
        }
    }
}

Knight::~Knight() {}
