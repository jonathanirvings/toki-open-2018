#include "mining.h"

#include <bits/stdc++.h>
using namespace std;

void findGold() {
  srand(time(0));

  vector<int> px(1000), py(1000);

  iota(px.begin(), px.end(), 1);
  random_shuffle(px.begin(), px.end());

  iota(py.begin(), py.end(), 1);
  random_shuffle(py.begin(), py.end());

  for (int i=0; i<1000; i++) {
    int x = px[i], y = py[i];
    if (!isIntegerDistance(x, y)) {
      continue;
    }
    
    int dx = (x == 1000 ? -1 : 1);
    int dy = (y == 1000 ? -1 : 1);
    
    if (isIntegerDistance(x + dx, y)) {
      for (int j=i; j<1000; j++) {
        if (isIntegerDistance(px[j], y + dy)) {
          answer(px[j], y);
          return;
        }
      }
    }

    if (isIntegerDistance(x, y + dy)) {
      for (int j=i+1; j<1000; j++) {
        if (isIntegerDistance(x + dx, py[j])) {
          answer(x, py[j]);
          return;
        }
      }
    }
  }
}
