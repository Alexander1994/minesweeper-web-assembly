
#include "Mine.h"
#include <string>
using namespace std;

Mine::Mine() {
  revealed = false;
  surroundingMineCount = 0;
}
bool Mine::isRevealed() {
  return revealed;
}
int Mine::getSurroundingMineCount() {
  return surroundingMineCount;
}

void Mine::setSurroundingMineCount(int srm) {
  surroundingMineCount = srm;
}

string Mine::toString() {
  string srm = to_string(surroundingMineCount);
  string r = to_string(revealed);
  return srm + r;
}
