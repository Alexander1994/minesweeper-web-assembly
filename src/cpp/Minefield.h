#ifndef MINEFIELD_H
#define MINEFIELD_H
#include "Mine.h"

class Minefield {
private:
  int height, width, mineCount;
  Mine **minefield;
  void incSurroundingMineCount(int x, int y);
  int* getSurroundingMineRange(int x, int y);
public:
  Minefield (int h, int w, int mc);
  ~Minefield();
  int revealLocation(int x, int y);
  void addMines(int clickX, int clickY);
  const char *toString();
};
#endif
