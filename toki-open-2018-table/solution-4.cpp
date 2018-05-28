#include "table.h"

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 4000 * 4000 + 5;

int fact[MAXN];
int ifact[MAXN];

int C(int n, int k) {
  return 1LL * fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}

int power(int x, int y, int mod) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % mod;
    x = 1LL * x * x % mod;
  }

  return ret;
}

int a[100][100];

int dp[100][100];
int f(int x, int sum) {
  if (x == 100) return sum == 13;
  if (~dp[x][sum]) return dp[x][sum];

  int ret = 0;
  for (int i=0; i<100; i++) {
    ret = (1LL * a[x][i] * f(x+1, (sum + i) % 100) + ret) % MOD;
  }

  return dp[x][sum] = ret;
}

int countSubsets(int M, int N, int K, std::vector<int> C, std::vector<int> D) {
  vector<int> counters(100, 0);

  for (int i=1; i<=M; i++) {
    int num = 1;
    for (int j=1; j<=N; j++) {
      num = num * i % 100;
      ++counters[num];
    }
  }

  for (int i=0; i<K; i++) {
    --counters[power(C[i], D[i], 100)];
  }

  fact[0] = 1;
  for (int i=1; i<MAXN; i++) fact[i] = 1LL * fact[i-1] * i % MOD;
  ifact[MAXN-1] = power(fact[MAXN-1], MOD-2, MOD);
  for (int i=MAXN-2; i>=0; i--) ifact[i] = 1LL * ifact[i+1] * (i+1) % MOD;

  for (int i=0; i<100; i++) {
    for (int j=0; j<=counters[i]; j++) {
      (a[i][i*j % 100] += ::C(counters[i], j)) %= MOD;
    }
  }

  memset(dp, -1, sizeof dp);
  return f(0, 0);
}
