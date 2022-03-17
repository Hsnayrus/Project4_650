#include "exerciser.h"

void exercise(connection * C) {
  query2(C, "LightBlue");
  query3(C, "Duke");
  query4(C, "NC", "LightBlue");
  query5(C, 3);
  query1(C, 1, 0, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
