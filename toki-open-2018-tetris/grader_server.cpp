#include "tetris.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <string>

static void wrongAnswer() {
  puts("WA");
  exit(0);
}

int main() {
  int N, Q;
  if (scanf("%d %d", &N, &Q) != 2) {
    wrongAnswer();
  }
  std::string S;
  if (!(std::cin >> S)) {
    wrongAnswer();
  }
  
  std::vector<int> ans = arrangeTetrominoes(N, S, Q);
  for (int i = 0; i < ans.size(); i++) {
    printf("%d\n", ans[i]);
  }
  if (!(std::cin >> std::ws).eof()) {
    wrongAnswer();
  }
  puts("df838ed4a0d56d7c080adbc162061887f7513f2f44d8892df50f99961f634ece");
  return 0;
}
