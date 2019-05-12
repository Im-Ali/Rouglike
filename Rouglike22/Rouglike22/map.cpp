#include "pch.h"
#include "map.h"


map::map() {}

bool map::isValidCoordinates(int x, int y) {
    return (x >= 0 && x < this->width) && (y >=0 && y < this->height);
}

map::~map() {}
