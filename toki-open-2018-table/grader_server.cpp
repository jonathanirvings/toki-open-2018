#include "table.h"

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
  int M, N, K;
  if (scanf("%d %d %d", &M, &N, &K) != 3) {
    wrongAnswer();
  }
  std::vector<int> C(K), D(K);
  for (int i = 0; i < K; ++i) {
    if (scanf("%d %d", &C[i], &D[i]) != 2) {
      wrongAnswer();
    }
  }
  
  printf("%d\n", countSubsets(M, N, K, C, D));
  if (!(std::cin >> std::ws).eof()) {
    wrongAnswer();
  }
  puts("df838ed4a0d56d7c080adbc162061887f7513f2f44d8892df50f99961f634ece");
  return 0;
}
