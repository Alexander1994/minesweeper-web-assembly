#ifndef MINE_H
#define MINE_H
#include <string>
using namespace std;
class Mine {
private:
  bool revealed;
  int mineCount; // 9 mine count = mine is present
public:
  Mine ();
  bool isRevealed();
  bool noMineCount();
  bool isMineInField();
  void setMineInField();
  void incMineCount();
  void reveal();
  string toString();
};
#endif
