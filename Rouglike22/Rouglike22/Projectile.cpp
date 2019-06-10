#include "pch.h"
#include "Projectile.h"


Projectile::Projectile(int damage, char sym, Coordinate pos, Direction direction) : Character(1, damage, sym, pos) {
    this->moveDirection = direction;
    this->savedDirection = direction;
    this->nonInteractedObject = 0;
    this->delay = 0;
}

void Projectile::SetMoveDirection(Direction direction) {
    if (direction == DirectionRandom)
        this->moveDirection = DirectionRandom;
    else
        this->moveDirection = this->savedDirection;
}

void Projectile::Interact(MapObject *c) {
    if (c->interactWithProjectile) {
        this->Attack(c);
        this->ReceiveDamage(this->GetHP());
    }
    else {
        this->nonInteractedObject = c;
        this->delay = 1;
    }
}

MapObject *Projectile::GetNonInteractedObject() {
    if (this->delay == 0)
        return this->nonInteractedObject;
    return 0;
}

void Projectile::ClearNonInteractedObject() {
    this->nonInteractedObject = 0;
}

const char *Projectile::GetName() {
    return "Projectile";
}

bool Projectile::isProjectile() {
    return true;
}

void Projectile::TickDone() {
    if (this->delay > 0)
        this->delay -= 1;
}

Projectile::~Projectile() {}
