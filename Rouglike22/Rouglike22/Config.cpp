#include "pch.h"
#include "Config.h"
#include "json.hpp"
#include <fstream>

Config& Config::CFG() {
    static Config c;
    return c;
}

Config::Config() {
    nlohmann::json json;
    std::ifstream stream("config.txt");
    stream >> json;

    playerHP             = (int)json["player"]["hp"];
    playerMana           = (int)json["player"]["mana"];
    playerAttack         = (int)json["player"]["attack"];
    playerSym            =      json["player"]["symbol"].get<std::string>()[0];
    playerShootingAttack = (int)json["player"]["shooting"]["attack"];
    playerShootingMana   = (int)json["player"]["shooting"]["mana"];
    playerShootingDelay  = (int)json["player"]["shooting"]["delay"];
    playerShootingSym    =      json["player"]["shooting"]["symbol"].get<std::string>()[0];
    playerManaregenValue = (int)json["player"]["manaregen"]["value"];
    playerManaregenDelay = (int)json["player"]["manaregen"]["delay"];

    dragonHP             = (int)json["dragon"]["hp"];
    dragonAttack         = (int)json["dragon"]["attack"];
    dragonSym            =      json["dragon"]["symbol"].get<std::string>()[0];
    dragonFireballAttack = (int)json["dragon"]["fireball"]["attack"];
    dragonFireballDelay  = (int)json["dragon"]["fireball"]["delay"];
    dragonFireballSym    =      json["dragon"]["fireball"]["symbol"].get<std::string>()[0];

    zombieHP             = (int)json["zombie"]["hp"];
    zombieAttack         = (int)json["zombie"]["attack"];
    zombieSym            =      json["zombie"]["symbol"].get<std::string>()[0];

    potionSym            =      json["potion"]["symbol"].get<std::string>()[0];
    potionValueMin       = (int)json["potion"]["value"]["min"];
    potionValueMax       = (int)json["potion"]["value"]["max"];

    princessSym          =      json["princess"]["symbol"].get<std::string>()[0];

    wallSym              =      json["wall"]["symbol"].get<std::string>()[0];

    mapDefaultSymbol     =      json["map"]["defaultSymbol"].get<std::string>()[0];
    mapWidth             = (int)json["map"]["width"];
    mapHeight            = (int)json["map"]["height"];

    gameDelay            = (int)json["game"]["delay"];
}

Config::~Config() {}
