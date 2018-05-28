#include "table.h"

#include <vector>
using namespace std;

int power(int x, int y) {
  int ret = 1;
  while (y--) ret *= x;
  return ret;
}

int countSubsets(int M, int N, int K, std::vector<int> C, std::vector<int> D) {
  vector<vector<bool>> cells = vector<vector<bool>>(M, vector<bool>(N, true));
  for (int i=0; i<K; i++) {
    cells[C[i] - 1][D[i] - 1] = false;
  }

  vector<int> nums;
  for (int i=0; i<M; i++) for (int j=0; j<N; j++) {
    if (cells[i][j]) {
      nums.push_back(power(i+1, j+1) % 100);
    }
  }

  int ret = 0;
  for (int i=0; i<1<<nums.size(); i++) {
    int sum = 0;
    for (int j=0; j<nums.size(); j++) {
      if (i >> j & 1) {
        sum += nums[j];
      }
    }

    if (sum % 100 == 13) ++ret;
  }

  return ret;
}
