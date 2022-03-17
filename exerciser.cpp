#include "exerciser.h"

void exercise(connection * C) {
  query2(C, "LightBlue");
  query3(C, "Duke");
  query4(C, "NC", "LightBlue");
  query5(C, 3);
  query1(C, 1, 0, 5, 0, 15, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0);
}
