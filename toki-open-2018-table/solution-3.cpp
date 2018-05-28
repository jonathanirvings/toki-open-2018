#include "table.h"

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int dp[500*500 + 5][105];
int f(int x, int sum, vector<int> &nums) {
  if (x == nums.size()) return sum == 13;
  if (~dp[x][sum]) return dp[x][sum];

  return dp[x][sum] = (
    f(x+1, sum, nums) +
    f(x+1, (sum + nums[x]) % 100, nums)
  ) % MOD;
}

bool cells[505][505];
int countSubsets(int M, int N, int K, std::vector<int> C, std::vector<int> D) {
  memset(cells, true, sizeof cells);
  for (int i=0; i<K; i++) {
    cells[C[i]][D[i]] = false;
  }

  vector<int> nums;
  for (int i=1; i<=M; i++) {
    int num = 1;
    for (int j=1; j<=N; j++) {
      num = num * i % 100;
      if (cells[i][j]) {
        nums.push_back(num);
      }
    }
  }

  memset(dp, -1, sizeof dp);
  return f(0, 0, nums);
}
