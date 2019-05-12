#include "pch.h"
#include <curses.h>
#include <iostream>
#include "GameProcess.h"
#include "Config.h"

int main() {

    GameProcess *gp = new GameProcess(new Config());
    delete gp;

}
