
#include "Mine.h"
#include <string>
using namespace std;

Mine::Mine() {
  revealed = false;
  mineCount = 0;
}

void Mine::reveal() {
  revealed = true;
}

bool Mine::isRevealed() {
  return revealed;
}

bool Mine::isMineInField() {
  return mineCount == 9;
}

bool Mine::noMineCount() {
  return mineCount == 0;
}

void Mine::setMineInField() {
  mineCount = 9;
}

void Mine::incMineCount() {
  mineCount++;
}

string Mine::toString() {
  string mc = to_string(mineCount);
  string r = to_string(revealed);
  return mc + r;
}
