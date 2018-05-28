#include "mining.h"

#include <vector>
using namespace std;

const int M = 1000;
const int N = 1000;
vector<vector<bool>> is_integer_distance;

void findGold() {
  is_integer_distance.resize(M, vector<bool>(N));
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      is_integer_distance[i][j] = isIntegerDistance(i + 1, j + 1);
    }
  }
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      bool valid_answer = true;
      for (int k = -1; k <= 1; ++k) {
        if (0 <= i + k && i + k < M && !is_integer_distance[i + k][j]) {
          valid_answer = false;
        }
      }
      for (int k = -1; k <= 1; ++k) {
        if (0 <= j + k && j + k < N && !is_integer_distance[i][j + k]) {
          valid_answer = false;
        }
      }
      if (valid_answer) {
        answer(i + 1, j + 1);
      }
    }
  }
}
