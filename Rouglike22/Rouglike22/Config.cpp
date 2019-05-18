#include "pch.h"
#include "Config.h"
#include "json.hpp"
#include <fstream>

Config::Config() {
    nlohmann::json json;
    std::ifstream stream("config.txt");
    stream >> json;

    this->playerSym = (int)json["player"]; // 'N';
    this->dragonSym = (int)json["dragon"]; // 'K';
    this->zombieSym = (int)json["zombie"]; // 'B';
    this->potionSym = (int)json["potion"]; // 'A';
}

Config::~Config() {}
