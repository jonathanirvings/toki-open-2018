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

  int mid = nums.size() >> 1;
  vector<int> counter(100, 0);

  for (int i=0; i<1<<mid; i++) {
    int sum = 0;
    for (int j=0; j<mid; j++) {
      if (i >> j & 1) {
        sum += nums[j];
      }
    }

    ++counter[sum % 100];
  }

  int ret = 0;
  for (int i=0; i < 1 << (int) nums.size() - mid; i++) {
    int sum = 0;
    for (int j=0; j<(int) nums.size()-mid; j++) {
      if (i >> j & 1) {
        sum += nums[mid + j];
      }
    }

    ret += counter[(113 - sum % 100) % 100];
  }

  return ret;
}
