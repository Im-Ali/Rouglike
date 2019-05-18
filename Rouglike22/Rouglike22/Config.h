#pragma once
class Config {
 public:
     int width, height;
     char playerSym;
     char dragonSym;
     char zombieSym;
     char potionSym;
  Config();
  void WriteConfig();
  ~Config();
};
