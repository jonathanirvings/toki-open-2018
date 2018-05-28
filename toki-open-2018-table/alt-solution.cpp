#include "table.h"

#include <bits/stdc++.h>
using namespace std;

const int MOD = 100;
const int MOD_TARGET = 13;

const int MOD_ANS = 1e9 + 7;

int modPow(int b, int n, int mod) {
  if (n == 0) {
    return 1;
  }
  int tmp = modPow(b, n / 2, mod);
  int tmp2 = (long long)tmp * tmp % mod;
  if (n % 2 == 0) {
    return tmp2;
  }
  return (long long)tmp2 * b % mod;
}

vector<int> multiply(vector<int> a, vector<int> b, int mod) {
  assert(a.size() == b.size());
  int n = a.size();
  vector<int> res(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      res[i] += (long long)a[j] * b[(i - j + n) % n] % mod;
      if (res[i] >= mod) {
        res[i] -= mod;
      }
    }
  }
  return res;
}

vector<int> pow(vector<int> a, long long b, int mod) {
  if (b == 0) {
    vector<int> res(a.size(), 0);
    res[0] = 1;
    return res;
  }
  vector<int> tmp = pow(a, b / 2, mod);
  vector<int> tmp2 = multiply(tmp, tmp, mod);
  if (b % 2 == 0) {
    return tmp2;
  }
  return multiply(tmp2, a, mod);
}

int countSubsets(int M, int N, int K, std::vector<int> C, std::vector<int> D) {
  vector<long long> occurences(MOD);
  for (int i = 0; i < MOD; ++i) {
    int base_with_mod_i = (M - (i == 0 ? MOD : i) + MOD) / MOD;
    vector<int> powers;
    int remaining_numbers = N;
    if (i == 0) {
      powers = {0};
    } else {
      int repeated_number = -1;
      unordered_set<int> seen_numbers;
      for (int j = 1; j <= N; ++j) {
        int i_pow_j = modPow(i, j, MOD);
        if (seen_numbers.count(i_pow_j)) {
          repeated_number = i_pow_j;
          break;
        }
        seen_numbers.insert(i_pow_j);
      }
      for (int j = 1; j <= N; ++j) {
        int i_pow_j = modPow(i, j, MOD);
        if (i_pow_j == repeated_number) {
          if (powers.size() > 0) {
            break;
          }
          powers.push_back(repeated_number);
        } else {
          if (powers.size() > 0) {
            powers.push_back(i_pow_j);
          } else {
            occurences[i_pow_j] += base_with_mod_i;
            --remaining_numbers;
          }
        }
      }
    }
    for (int j = 0; j < powers.size(); ++j) {
      occurences[powers[j]] += 
          (long long)base_with_mod_i *
          ((remaining_numbers - j + powers.size() - 1) / powers.size());
    }
  }
  for (int i = 0; i < K; ++i) {
    --occurences[modPow(C[i], D[i], MOD)];
  }
  vector<vector<int>> DP(MOD + 1, vector<int>(MOD, 0));
  DP[MOD][MOD_TARGET] = 1;
  for (int i = MOD - 1; i >= 0; --i) {
    vector<int> possibilities_vector(MOD);
    possibilities_vector[0] += 1;
    possibilities_vector[i] += 1;
    
    possibilities_vector = pow(possibilities_vector, occurences[i], MOD_ANS);
    for (int j = 0; j < MOD; ++j) {
      for (int k = 0; k < MOD; ++k) {
        DP[i][j] += (long long)possibilities_vector[(k - j + MOD) % MOD]
                  * DP[i + 1][k] % MOD_ANS;
        if (DP[i][j] >= MOD_ANS) {
          DP[i][j] -= MOD_ANS;
        }
      }
    }
  }
  return DP[0][0];
}
