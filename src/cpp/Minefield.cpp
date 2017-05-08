#include "Minefield.h"

#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


template <typename Map>
bool map_compare (Map const &lhs, Map const &rhs) {
    return lhs.size() == rhs.size() &&
           equal(lhs.begin(), lhs.end(), rhs.begin());
}

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
    vector<map<char,int> > emptyCoordSet;
    map<char,int> firstClick, coordToPush;
    firstClick['x'] = x;
    firstClick['y'] = y;
    emptyCoordSet.push_back(firstClick);
    for (it = 0; it < emptyCoordSet.size(); it++) {
      currX = emptyCoordSet[it]['x'];
      currY = emptyCoordSet[it]['y'];
      startX = (currX - 1 < 0) ? currX : currX-1;
      startY = (currY - 1 < 0) ? currY : currY-1;
      endX = (currX + 1 >= width) ? currX : currX+1;
      endY = (currY + 1 >= height) ? currY : currY+1;

      for (int i = startX; i <= endX; i++) {
        for (int j = startY; j <= endY; j++) {
          coordToPush['x'] = i;
          coordToPush['y'] = j;
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
  int* mineRange = getSurroundingMineRange(x, y);
  int startX = mineRange[2], endX = mineRange[3], startY = mineRange[0], endY = mineRange[1];

  for (int i = startX; i <= endX; i++) {
    for (int j = startY; j <= endY; j++) {
      if (!minefield[j][i].isMineInField()) {
        minefield[j][i].incMineCount();
      }
    }
  }
  delete [] mineRange;

}

void Minefield::addMines(int clickX, int clickY) {
  int* mineRange = getSurroundingMineRange(clickX, clickY);
  int startX = mineRange[0], endX = mineRange[1], startY = mineRange[2], endY = mineRange[3];

  srand(time(NULL));

  map<char,int> coord;
  vector<map<char,int> >::const_iterator first, last;
  vector<map<char,int> > allMines;
  for (size_t y = 0; y < height; y++) {
    for (size_t x = 0; x < width; x++) {
      if ( y < startY || y > endY || x < startX || x > endX ){
        coord['x'] = x;
        coord['y'] = y;
        allMines.push_back(coord);
      }
    }
  }
  random_shuffle(allMines.begin(), allMines.end());
  int subArrayStart, randomMinesLength = allMines.size() - mineCount;
  subArrayStart = (randomMinesLength) ? rand() % randomMinesLength : 0;
  printf("start: %i\n", subArrayStart);
  first = allMines.begin() + subArrayStart;
  last = allMines.begin() + subArrayStart + mineCount;
  vector<map<char,int> > randomMines(first, last);

  int randomMinesCount = randomMines.size();
  for (size_t i = 0; i < randomMinesCount; i++) {
    coord = randomMines[i];
    minefield[coord['y']][coord['x']].setMineInField();
    incSurroundingMineCount(coord['x'],coord['y']);
  }
}

int* Minefield::getSurroundingMineRange(int x, int y) {
  int* mineRange = new int[4];
  mineRange[0] = (y - 1 < 0) ? y : y-1;        // startX
  mineRange[1] = (y + 1 > height-1) ? y : y+1; // endX
  mineRange[2] = (x - 1 < 0) ? x : x-1;        // startY
  mineRange[3] = (x + 1 > width-1) ? x : x+1;  // endY
  return mineRange;
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
