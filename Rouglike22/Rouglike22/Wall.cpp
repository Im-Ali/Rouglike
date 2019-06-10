#include "pch.h"
#include "Wall.h"


Wall::Wall(char sym, Coordinate position) : Character(100, 0, sym, position) {
    this->canMove = false;
}

void Wall::Interact(MapObject *c) {}

void Wall::ReceiveDamage(int damage) {
}

const char *Wall::GetName() {
    return "Wall";
}

Wall::~Wall() {}
