#include "pch.h"
#include <stdio.h>
#include "Zombie.h"
#include "Config.h"

int ZombieOrderNumber = 0;
char str[20];

Zombie::Zombie(char c, Coordinate position) : Character(Config::CFG().zombieHP, Config::CFG().zombieAttack, c, position) {
    ZombieOrderNumber++;
    this->orderNumber = ZombieOrderNumber;
}

void Zombie::Interact(MapObject *c) {
    this->Attack(c);
}

const char *Zombie::GetName() {
    sprintf(str, "Zombie%d", this->orderNumber);
    return str;
}

Zombie::~Zombie() {}
