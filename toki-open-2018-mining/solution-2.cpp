#include "mining.h"

#include <bits/stdc++.h>
using namespace std;

const int M = 1000;
const int N = 1000;

void findGold() {
  unordered_set<int> row, column;
  for (int i = 1; i <= M; ++i) {
    row.insert(i);
  }
  for (int i = 1; i <= N; ++i) {
    column.insert(i);
  }
  for (int i = 1; i <= 2; ++i) {
    for (int j = 1; j <= N; ++j) {
      if (!isIntegerDistance(i, j)) {
        column.erase(j);
      }
    }
  }
  for (int i = 1; i <= M; ++i) {
    for (int j = 1; j <= 2; ++j) {
      if (!isIntegerDistance(i, j)) {
        row.erase(i);
      }
    }
  }
  answer(*(row.begin()), *(column.begin()));
}
