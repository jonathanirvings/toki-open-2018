#include "tetris.h"

#include <cassert>

#include <string>
#include <vector>

using namespace std;

std::vector<int> arrangeTetrominoes(int N, std::string S, int Q) {
  int lastJOrL = -1;
  vector<int> ans(N);
  for (int i = 0; i < N; i++) {
    if (S[i] == 'O') {
      ans[i] = 0;
    } else {
      if (lastJOrL == -1) {
        lastJOrL = i;
      } else {
        if (S[lastJOrL] == 'J' && S[i] == 'L') {
          ans[lastJOrL] = 1;
          ans[i] = 3;
        } else if (S[lastJOrL] == 'L' && S[i] == 'J') {
          ans[lastJOrL] = 3;
          ans[i] = 1;
        } else if (S[lastJOrL] == 'J' && S[i] == 'J') {
          ans[lastJOrL] = 3;
          ans[i] = 1;
        } else if (S[lastJOrL] == 'L' && S[i] == 'L') {
          ans[lastJOrL] = 1;
          ans[i] = 3;
        } else assert(false);
        lastJOrL = -1;
      }
    }
  }
  return lastJOrL == -1 ? ans : vector<int>();
}
