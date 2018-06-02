#include "tile.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <vector>

static void wrongAnswer() {
  puts("WA");
  exit(0);
}

int main() {
  int N, K, M, Q;
  if (scanf("%d %d %d %d", &N, &K, &M, &Q) != 4) {
    wrongAnswer();
  }
  
  std::vector<int> A(M);
  for (int i = 0; i < M; ++i) {
    if (scanf("%d", &A[i]) != 1) {
      wrongAnswer();
    }
  }

  init(N, K, Q, M, A);

  for (int i = 0; i < Q; ++i) {
    int L, R;
    if (scanf("%d %d", &L, &R) != 2) {
      wrongAnswer();
    }
    printf("%d\n", getNumberOfSpecialTiles(L, R));
  }
  if (!(std::cin >> std::ws).eof()) {
    wrongAnswer();
  }
  puts("df838ed4a0d56d7c080adbc162061887f7513f2f44d8892df50f99961f634ece");
  return 0;
}
