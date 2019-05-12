#pragma once
#include "Character.h"

class Log {
 private:
     static void Write(const char *format);

 public:
     static void WriteMove(Character *c, bool move);
     static void WriteInteraction(Character *c1, MapObject *c2);
     static void WriteTicks(int ticks);

  ~Log();
};
