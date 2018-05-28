#include "tile.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adv;
vector<int> A;
const int LOGM = 20;

void init(int N, int K, int Q, int M, std::vector<int> A) {
  adv.resize(LOGM, vector<int>(N + 1, 0));
  ::A = A;
  vector<int> holes(N, 0);
  for (int i = 0; i < M; ++i) {
    holes[A[i] - 1] = 1;
  }
  adv[0][N] = N;
  for (int i = N - 1; i >= 0; --i) {
    if (holes[i] == 1) {
      adv[0][i] = min(N, i + K);
    } else {
      adv[0][i] = adv[0][i + 1];
    }
  }
  for (int i = 1; i < LOGM; ++i) {
    adv[i][N] = N;
    for (int j = N - 1; j >= 0; --j) {
      if (holes[j] == 1) {
        adv[i][j] = adv[i - 1][adv[i - 1][j]];
      } else {
        adv[i][j] = adv[i][j + 1];
      }
    }
  }
}

int getNumberOfSpecialTiles(int L, int R) {
  int result = 0;
  int now = L;
  for (int i = LOGM - 1; i >= 0; --i) {
    if (adv[i][now - 1] + 1 <= R) {
      result += (1 << i);
      now = adv[i][now - 1] + 1;
    }
  }
  if (lower_bound(A.begin(), A.end(), now)
      < upper_bound(A.begin(), A.end(), R)) {
    return result + 1;
  } else {
    return result;
  }
}
