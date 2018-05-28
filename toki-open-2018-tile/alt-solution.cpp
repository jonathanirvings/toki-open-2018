#include "tile.h"

#include <bits/stdc++.h>
using namespace std;

#define ALL(a) begin(a), end(a)

using vi = vector<int>;

namespace {

int k, m;
vi a;
vector<vi> st;

int getFirstBadIndex(int x) {
  auto it = lower_bound(ALL(a), x);
  return it == end(a) ? m : it - begin(a);
}

}  // namespace

void init(int N_asdf, int K_asdf, int Q_asdf, int M_asdf, vector<int> A_asdf) {
  k = K_asdf;
  m = M_asdf;
  a = A_asdf;
  a.push_back(N_asdf + 1);
  sort(ALL(a));
  st.assign(20, vi(m + 1, -1));
  for (int i = 0; i < m; i++) {
    st[0][i] = getFirstBadIndex(a[i] + k);
    assert(st[0][i] >= i);
  }
  st[0][m] = m + 1;
  for (int i = 1; i < 20; i++) {
    for (int j = 0; j < m; j++) {
      if (st[i - 1][j] == -1) {
        break;
      }
      st[i][j] = st[i - 1][j] == m + 1 ? m + 1 : st[i - 1][st[i - 1][j]];
    }
    st[i][m] = m + 1;
  }
}

int getNumberOfSpecialTiles(int L, int R) {
  int ll = getFirstBadIndex(L);
  int rr = getFirstBadIndex(R + 1) - 1;
  if (ll > rr) {
    return 0;
  }
  int result = 0;
  for (int i = 19; i >= 0 && ll <= rr; i--) {
    if (st[i][ll] == -1) {
      continue;
    }
    if (st[i][ll] <= rr + 1) {
      result += 1 << i;
      ll = st[i][ll];
    }
  }
  return ll == rr + 1 ? result : result + 1;
}
