#include "pch.h"
#include "Princess.h"


Princess::Princess(Coordinate position): Character(25, 0, 'P', position) {
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
