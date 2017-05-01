#ifndef MINEFIELD_H
#define MINEFIELD_H
#include "Mine.h"
#include <string>
using namespace std;

class Minefield {
private:
  int height, width, mineCount;
  Mine **minefield;
  void incSurroundingMineCount(int x, int y);
public:
  Minefield (int h, int w, int mc);
  ~Minefield();
  int revealLocation(int x, int y);
  void addMines();
  const char *toString();
};
#endif
