
#include <stdlib.h>
#include <emscripten/emscripten.h>

using namespace std;

#include "Minefield.h"

Minefield *minefield;

extern "C" {
 int EMSCRIPTEN_KEEPALIVE revealLocation(int x, int y) {
    return minefield->revealLocation(x,y);
  }
  void EMSCRIPTEN_KEEPALIVE createMineField(int height, int width, int minecount) {
    minefield = new Minefield(height, width, minecount);
  }
  void EMSCRIPTEN_KEEPALIVE addMines(int x, int y) { // coordinates for first click
    minefield->addMines(x, y);
  }
  void EMSCRIPTEN_KEEPALIVE clearMemory() {
    delete minefield;
  }
  const char* EMSCRIPTEN_KEEPALIVE viewBoard() {
    return minefield->toString();
  }
}
