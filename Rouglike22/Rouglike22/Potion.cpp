#include "pch.h"
#include "Potion.h"


Potion::Potion(int hp, char sym, Coordinate coord) : MapObject(sym, coord) {
    this->upHP = hp;
    this->canBeJumped = true;
    this->interactWithProjectile = false;
}

void Potion::Interact(MapObject *c) {
    c->RestoreHP(this->upHP);
}
    
const char *Potion::GetName() {
    return "Potion";
}

Potion::~Potion() {}
