#include "tile.h"
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> answer;

void init(int N, int K, int Q, int M, std::vector<int> A) {
  answer.resize(N, vector<int>(N));
  vector<int> holes(N, 0);
  for (int i = 0; i < M; ++i) {
    holes[A[i] - 1] = 1;
  }
  for (int i = 0; i < N; ++i) {
    int tiles = 0;
    int next_cover = i;
    for (int j = i; j < N; ++j) {
      if (holes[j] == 1) {
        if (next_cover <= j) {
          next_cover = j + K;
          ++tiles;
        }
      }
      answer[i][j] = tiles;
    }
  }
}

int getNumberOfSpecialTiles(int L, int R) {
  return answer[L - 1][R - 1];
}
