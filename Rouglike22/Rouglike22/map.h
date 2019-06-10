#pragma once

class map {
public:
     int width, height;
     char **data;
     
     bool isValidCoordinates(int x, int y);
     map(int width, int height);
     ~map();
};
