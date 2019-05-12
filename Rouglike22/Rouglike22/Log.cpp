#include "pch.h"
#include "Log.h"
#include <stdio.h>

void Log::Write(const char *text) {
  FILE *f = fopen("gamelog.txt", "a");
  fprintf(f, text);
  fprintf(f, "\r\n");
  fclose(f);
}

void Log::WriteMove(Character *ch, bool move) {
  char str[255];
  char dir[10] = "?";

  if (move) {
    if (ch->GetMoveDirection() == 1)
          sprintf(dir, "влево");
      else if (ch->GetMoveDirection() == 2) 
          sprintf(dir, "вправо");
      else if (ch->GetMoveDirection() == 3)
          sprintf(dir, "вверх");
      else if (ch->GetMoveDirection() == 4)
          sprintf(dir, "вниз");
      sprintf(str, "%s переместился %s", ch->GetName(), dir);
      Log::Write(str);
  }
}

void Log::WriteInteraction(Character *c1, MapObject *c2) { 
    char str[255];
    sprintf(str, "%s столкнулся с %s", c1->GetName(), c2->GetName());
    Log::Write(str);
    sprintf(str, "%s hp: %d", c1->GetName(), c1->GetHP());
    Log::Write(str);
    sprintf(str, "%s hp: %d", c2->GetName(), c2->GetHP());
    Log::Write(str);
}

void Log::WriteTicks(int ticks) {
  char str[255];
  sprintf(str, "Tick: %d", ticks);
  Log::Write(str);
}

Log::~Log() {}
