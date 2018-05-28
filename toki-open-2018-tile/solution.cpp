#include "tile.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adv;
vector<int> A;
const int LOGM = 20;

void init(int N, int K, int Q, int M, std::vector<int> A) {
  ::A = A;
  adv.resize(LOGM, vector<int>(M + 1));
  int R = 0;
  for (int i = 0; i < M + 1; ++i) {
    while (R < M && A[i] + K - 1 >= A[R]) {
      ++R;
    }
    adv[0][i] = R;
  }
  for (int i = 1; i < LOGM; ++i) {
    for (int j = 0; j < M + 1; ++j) {
      adv[i][j] = adv[i - 1][adv[i - 1][j]];
    }
  }
}

int getNumberOfSpecialTiles(int L, int R) {
  int result = 0;
  int now = lower_bound(A.begin(), A.end(), L) - A.begin();
  int finish = upper_bound(A.begin(), A.end(), R) - A.begin();
  for (int i = LOGM - 1; i >= 0; --i) {
    if (adv[i][now] < finish) {
      now = adv[i][now];
      result += (1 << i);
    }
  }
  if (now == finish) {
    return result;
  }
  return result + 1;
}
