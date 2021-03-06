#ifndef MINEFIELD_H
#define MINEFIELD_H
#include "Mine.h"
#include <map>
#include <string>


class Minefield {
private:
  int height, width, mineCount;
  Mine **minefield;
  void incSurroundingMineCount(int x, int y);
  std::map<string, int> getSurroundingMineRange(int x, int y);
public:
  Minefield (int h, int w, int mc);
  ~Minefield();
  int revealLocation(int x, int y);
  void revealAllMines();
  void addMines(int clickX, int clickY);
  std::vector<Mine> getRevealedMines();
  const char *toString();
};
#endif
