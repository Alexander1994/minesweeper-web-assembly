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
  return minefield[x][y].getMineCount();
}

void Minefield::incSurroundingMineCount(int x, int y) {
  int startX = (x - 1 < 0) ? x : x-1;
  int startY = (y - 1 < 0) ? y : y-1;
  int endX = (x + 1 > width) ? x : x+1;
  int endY = (y + 1 > height) ? y : y+1;

  for (int i = startX; i <= endX; i++) {
    for (int j = startY; j <= endY; j++) {
      if (minefield[j][i].getMineCount() != 9) {
        minefield[j][i].incMineCount();
      }
    }
  }
}

void Minefield::addMines() {
  srand(time(NULL));
  int x, y, i = 0;
  while (i < mineCount) {
    x = rand() % width;
    y = rand() % height;
    if (minefield[y][x].getMineCount() != 9) {
      minefield[y][x].setMineInField();
      incSurroundingMineCount(x,y);
      i++;
    }
  }
}
const char* Minefield::toString() {
  string minefieldstring = "";
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      minefieldstring += minefield[i][j].toString();
    }
  }
  return minefieldstring.c_str();
}
