#include "tile.h"
#include <bits/stdc++.h>
using namespace std;

int N, K, M;
vector<int> A;

void init(int N, int K, int Q, int M, std::vector<int> A) {
  ::N = N;
  ::K = K;
  ::M = M;
  ::A = A;
}

int getNumberOfSpecialTiles(int L, int R) {
  int next_cover = L;
  int answer = 0;
  for (int i = 0; i < M; ++i) {
    if (A[i] > R) {
      break;
    }
    if (next_cover <= A[i]) {
      ++answer;
      next_cover = A[i] + K;
    }
  }
  return answer;
}
