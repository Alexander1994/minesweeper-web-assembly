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
  int getMineCount();
  void setMineInField();
  void incMineCount();
  string toString();
};
#endif
