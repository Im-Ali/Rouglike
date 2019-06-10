#include "pch.h"
#include "map.h"
#include <stdio.h>


map::map(int width, int height) {
    this->width = width;
    this->height = height;

    char buf[2];
    FILE *f = fopen("map.txt", "r");
    this->data = new char*[this->height];
    for (int i = 0; i < this->height; i++) {
        this->data[i] = new char[this->width];
        fread(data[i], 1, this->width, f);
        fread(buf, 1, 1, f);
    }
}

bool map::isValidCoordinates(int x, int y) {
    return (x >= 0 && x < this->width) && (y >=0 && y < this->height);
}

map::~map() {
    for (int i = 0; i < this->height; i++)
        delete this->data[i];
    delete this->data;
}
