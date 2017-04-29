#ifndef MINE_H
#define MINE_H
#include <string>
using namespace std;
class Mine {
private:
  bool revealed;
  int surroundingMineCount;
public:
  Mine ();
  bool isRevealed();
  int getSurroundingMineCount();
  void setSurroundingMineCount(int srm);
  string toString();
};
#endif
