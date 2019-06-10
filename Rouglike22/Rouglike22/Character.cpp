#include "pch.h"
#include "Character.h"

Character::Character(int hp, int damage, char sym, Coordinate pos) : MapObject(sym, pos) {
    this->hp = hp;
    this->maxHP = this->hp;
    this->damage = damage;
    this->mana = 0;
    this->canMove = true;
    this->moveDirection = DirectionRandom;
}

int Character::GetMP() { 
    return this->mana;
}

int Character::GetDamage(){
    return this->damage;
}

void Character::MoveTo(Coordinate position) {
    this->position = position;
}

void Character::Attack(MapObject *c) {
    c->ReceiveDamage(this->damage);
}

Direction Character::GetMoveDirection() {
    return this->moveDirection;
}

void Character::SetMoveDirection(Direction direction) {
    this->moveDirection = direction;
}

Character::~Character() {}