#pragma once
class Config {
public:
    int playerHP;
    int playerMana;
    int playerAttack;
    char playerSym;
    int playerShootingAttack;
    int playerShootingMana;
    int playerShootingDelay;
    int playerShootingSym;
    int playerManaregenValue;
    int playerManaregenDelay;

    int dragonHP;
    int dragonAttack;
    char dragonSym;
    int dragonFireballAttack;
    int dragonFireballDelay;
    int dragonFireballSym;

    int zombieHP;
    int zombieAttack;
    char zombieSym;

    char potionSym;
    int potionValueMin;
    int potionValueMax;

    char princessSym;

    char wallSym;

    char mapDefaultSymbol;
    int mapWidth;
    int mapHeight;

    int gameDelay;

    static Config& CFG();

private:
    Config();
    ~Config();
    Config(Config const&);
    Config& operator=(Config const&);
};