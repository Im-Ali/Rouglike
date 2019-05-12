#include "pch.h"
#include "Wall.h"


Wall::Wall(Coordinate position) : Character(100, 0, '#', position) {
    this->canMove = false;
}

void Wall::Interact(MapObject *c) {}

void Wall::ReceiveDamage(int damage) {
}

const char *Wall::GetName() {
    return "Wall";
}

Wall::~Wall() {}
