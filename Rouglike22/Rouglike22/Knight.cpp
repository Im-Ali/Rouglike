#include "pch.h"
#include "Knight.h"
#include "Config.h"

Knight::Knight(int hp, int damage, char sym, Coordinate pos) : Character(hp, damage, sym, pos)
{
    this->maxMana = Config::CFG().playerMana;
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
    if (this->mana >= Config::CFG().playerShootingMana && this->delay == 0) {
        this->mana -= Config::CFG().playerShootingMana;
        this->delay = Config::CFG().playerShootingDelay;
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
            int mana = Config::CFG().playerManaregenValue;
            if (this->mana + mana > this->maxMana)
                this->mana = this->maxMana;
            else
                this->mana += mana;
            this->manaRestoreDelay = Config::CFG().playerManaregenDelay;
        }
    }
}

Knight::~Knight() {}
