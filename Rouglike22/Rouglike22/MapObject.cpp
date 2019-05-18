#include "pch.h"
#include "MapObject.h"


MapObject::MapObject(char sym, Coordinate pos) {    
    this->hp = 1;
    this->maxHP = this->hp;
    this->position = pos;
    this->sym = sym;
}

Coordinate MapObject::GetPos() { return this->position; }

int MapObject::GetHP() { return this->hp; }

char MapObject::GetSym() { return this->sym; }

bool MapObject::isPrincess() { return false; }          

bool MapObject::isProjectile() { return false; }

void MapObject::ReceiveDamage(int damage) { this->hp -= damage; }

void MapObject::RestoreHP(int hp) {
    if (this->hp + hp > this->maxHP)
        this->hp = this->maxHP;
    else
        this->hp += hp;
}

void MapObject::TickDone() {}

MapObject::~MapObject() {}
