#include "Minefield.h"

#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>

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

int Minefield::revealLocation(int x, int y) { // 1 == mine hit, otherwise 0
  if (minefield[x][y].isMineInField()) {
    return 1;
  } else if (minefield[x][y].noMineCount()) { // no mine count in field

    int startX, startY, endX, endY, currX, currY, coordDivider, it;
    string coordToPush, coord;
    vector<string> emptyCoordSet;
    emptyCoordSet.push_back(to_string(x) + " " + to_string(y));
    for (it = 0; it < emptyCoordSet.size(); it++) {
      coord = emptyCoordSet[it];
      coordDivider = coord.find(' ');
      currX = stoi(coord.substr(0, coordDivider));
      currY = stoi(coord.substr(coordDivider));
      startX = (currX - 1 < 0) ? currX : currX-1;
      startY = (currY - 1 < 0) ? currY : currY-1;
      endX = (currX + 1 >= width) ? currX : currX+1;
      endY = (currY + 1 >= height) ? currY : currY+1;
      for (int i = startX; i <= endX; i++) {
        for (int j = startY; j <= endY; j++) {
          coordToPush = to_string(i) + " " + to_string(j);
          if (minefield[i][j].noMineCount() && find(emptyCoordSet.begin(), emptyCoordSet.end(), coordToPush) == emptyCoordSet.end()) {
            emptyCoordSet.push_back(coordToPush);
          }
          minefield[i][j].reveal();

        }
      }
    }

  } else { // number in field
    minefield[x][y].reveal();
  }
  return 0;
}

void Minefield::incSurroundingMineCount(int x, int y) {
  int startX = (x - 1 < 0) ? x : x-1;
  int startY = (y - 1 < 0) ? y : y-1;
  int endX = (x + 1 > width) ? x : x+1;
  int endY = (y + 1 > height) ? y : y+1;

  for (int i = startX; i <= endX; i++) {
    for (int j = startY; j <= endY; j++) {
      if (!minefield[j][i].isMineInField()) {
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
    if (!minefield[y][x].isMineInField()) {
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
