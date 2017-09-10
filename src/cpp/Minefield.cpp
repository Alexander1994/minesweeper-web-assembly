#include "Minefield.h"

#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stdexcept>

using namespace std;
/*
 for () for ()
mf[x][y]
*/
template <typename Map>
bool map_compare (Map const &lhs, Map const &rhs) {
    return lhs.size() == rhs.size() &&
           equal(lhs.begin(), lhs.end(), rhs.begin());
}

Minefield::Minefield(int h, int w, int mc) {
  mineCount = mc, height = h, width = w;
  if (mineCount > height * width - 9) {
    throw invalid_argument("more mines then field can hold");
  }
  minefield = new Mine*[height];
  for (int i = 0; i < height; i++) {
    minefield[i] = new Mine[width];
  }
}

Minefield::~Minefield() {
  for (int i = 0; i < height; i++) {
    delete[] minefield[i];
  }
  delete[] minefield;
}

int Minefield::revealLocation(int x, int y) { // 1 == mine hit, otherwise 0
  if (minefield[x][y].isMineInField()) {
    return 1;
  } else if (minefield[x][y].noMineCount()) { // no mine count in field

    int currX, currY, coordDivider, it;
    vector<map<char,int> > emptyCoordSet;
    map<char,int> firstClick, coordToPush;
    firstClick['x'] = x;
    firstClick['y'] = y;
    emptyCoordSet.push_back(firstClick);
    for (it = 0; it < emptyCoordSet.size(); it++) {
      currX = emptyCoordSet[it]['x'];
      currY = emptyCoordSet[it]['y'];
      map<string, int> mineRange = getSurroundingMineRange(currX, currY);

      for (int i = mineRange["startX"]; i <= mineRange["endX"]; i++) {
        for (int j = mineRange["startY"]; j <= mineRange["endY"]; j++) {
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
  map<string, int> mineRange = getSurroundingMineRange(x, y);
  for (int i = mineRange["startX"]; i <= mineRange["endX"]; i++) {
    for (int j = mineRange["startY"]; j <= mineRange["endY"]; j++) {
      if (!minefield[i][j].isMineInField()) {
        minefield[i][j].incMineCount();
      }
    }
  }

}

void Minefield::addMines(int clickX, int clickY) {
  map<string, int> mineRange = getSurroundingMineRange(clickX, clickY);
  srand(time(NULL));

  map<char,int> coord;
  vector<map<char,int> >::const_iterator first, last;
  vector<map<char,int> > allMines;
  for (size_t y = 0; y < height; y++) {
    for (size_t x = 0; x < width; x++) {
      if (y < mineRange["startY"] || y > mineRange["endY"] || x < mineRange["startX"] || x > mineRange["endX"]) {
        coord['x'] = x;
        coord['y'] = y;
        allMines.push_back(coord);
      }
    }
  }
  random_shuffle(allMines.begin(), allMines.end());
  int randomMinesLength = allMines.size() - mineCount;
  int subArrayStart = (randomMinesLength) ? rand() % randomMinesLength : 0;
  first = allMines.begin() + subArrayStart;
  last = allMines.begin() + subArrayStart + mineCount;
  vector<map<char,int> > randomMines(first, last);

  int randomMinesCount = randomMines.size();
  for (size_t i = 0; i < randomMinesCount; i++) {
    coord = randomMines[i];
    minefield[coord['x']][coord['y']].setMineInField();
    incSurroundingMineCount(coord['x'],coord['y']);
  }
}

map<string, int> Minefield::getSurroundingMineRange(int x, int y) {
  map<string, int> mineRange;
  mineRange["startX"] = (x == 0) ? x : x-1;
  mineRange["endX"] = (x == width-1) ? x : x+1;
  mineRange["startY"] = (y == 0) ? y : y-1;
  mineRange["endY"] = (y == height-1) ? y : y+1;
  return mineRange;
}

vector<Mine> Minefield::getRevealedMines() {
  vector<Mine> revealedMines;
  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      if (minefield[i][j].isRevealed())
        revealedMines.push_back(minefield[i][j]);
    }
  }
  return revealedMines;
}

const char* Minefield::toString() {
  string minefieldstring = "";
  string tmp = "";
  for (size_t i = 0; i < width; i++) {
    for (size_t j = 0; j < height; j++) {
      minefieldstring += minefield[i][j].toString();
    }
  }
  return minefieldstring.c_str();
}
