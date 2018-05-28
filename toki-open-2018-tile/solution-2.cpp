#include "tile.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> answer;
vector<int> A;

void init(int N, int K, int Q, int M, std::vector<int> A) {
  ::A = A;
  answer.resize(M, vector<int>(M));
  for (int i = 0; i < M; ++i) {
    int tiles = 0;
    int next_cover = i;
    for (int j = i; j < M; ++j) {
      if (next_cover <= A[j]) {
        ++tiles;
        next_cover = A[j] + K;
      }
      answer[i][j] = tiles;
    }
  }
}

int getNumberOfSpecialTiles(int L, int R) {
  int l = lower_bound(A.begin(), A.end(), L) - A.begin();
  int r = upper_bound(A.begin(), A.end(), R) - A.begin() - 1;
  if (l > r) {
    return 0;
  }
  return answer[l][r];
}
