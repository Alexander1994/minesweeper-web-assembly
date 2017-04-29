#include "Minefield.h"

#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

Minefield::Minefield(int h, int w, int mc) {
  mineCount = mc, height = h, width = w;
  minefield = new Mine*[height];
  for (int i = 0; i < height; i++) {
    minefield[i] = new Mine[width];
  }
}
Minefield::~Minefield() {
  for (int i = 0; i < height; i++) {
    delete minefield[i];
  }
  delete minefield;
}

int Minefield::revealLocation(int x, int y) {
  return minefield[x][y].getSurroundingMineCount();
}

void Minefield::addMines() {
  srand(time(NULL));
  int x, y, i = 0;
  while (i < mineCount) {
    x = rand() % height;
    y = rand() % width;
    if (minefield[x][y].getSurroundingMineCount() != 9) {
      minefield[x][y].setSurroundingMineCount(9);
      i++;
    }
  }
}
const char *Minefield::toString() {
  string minefieldstring = "";
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      minefieldstring += minefield[i][j].toString();
    }
  }
  return minefieldstring.c_str();
}
