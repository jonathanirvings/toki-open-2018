#include "tour.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <string>
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
  
  std::vector<std::string> S(N);
  for (int i = 0; i < N; ++i) {
    if (!(std::cin >> S[i])) {
      wrongAnswer();
    }
  }

  printf("%d\n", getShortestTour(N, S));
  if (!(std::cin >> std::ws).eof()) {
    wrongAnswer();
  }
  puts("df838ed4a0d56d7c080adbc162061887f7513f2f44d8892df50f99961f634ece");
  return 0;
}
