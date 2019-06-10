#include "pch.h"
#include "Princess.h"


Princess::Princess(char sym, Coordinate position): Character(25, 0, sym, position) {
    this->mana= 10;
    this->canMove = false;
}

bool Princess::isPrincess() {
    return true;
}

void Princess::Interact(MapObject *c) {}

const char *Princess::GetName() {
    return "Princess";
}

void Princess::ReceiveDamage(int damage) {}

Princess::~Princess() {}
