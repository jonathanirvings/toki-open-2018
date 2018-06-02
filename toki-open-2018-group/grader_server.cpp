#include "group.h"

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
  int N;
  if (scanf("%d", &N) != 1) {
    wrongAnswer();
  }

  std::vector<int> X(N), Y(N);
  for (int i = 0; i < N; ++i) {
    if (scanf("%d %d", &X[i], &Y[i]) != 2) {
      wrongAnswer();
    }
  }

  printf("%d\n", getMinimumDelay(N, X, Y));
  if (!(std::cin >> std::ws).eof()) {
    wrongAnswer();
  }
  puts("df838ed4a0d56d7c080adbc162061887f7513f2f44d8892df50f99961f634ece");
  return 0;
}
