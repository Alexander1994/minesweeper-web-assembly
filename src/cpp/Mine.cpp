
#include "Mine.h"
#include <string>
using namespace std;

Mine::Mine() {
  revealed = false;
  mineCount = 0;
}
bool Mine::isRevealed() {
  return revealed;
}
int Mine::getMineCount() {
  return mineCount;
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
