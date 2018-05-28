#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ALL(a) begin(a), end(a)
#define SZ(a) ((int)(a).size())

#ifdef __DEBUG
#define debug if (true)
#else
#define debug if (false)
#endif

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

template <typename T> using V = vector<T>;
template <typename T> using VV = vector<V<T>>;
template <typename T> using VVV = vector<VV<T>>;

enum RowState: int {
  EMPTY = 0,
  RIGHT = 1,
  LEFT = 2,
  BOTH = 3,
};

using vrs = vector<RowState>;

const vrs STATES[5] = {
  {LEFT, LEFT},
  {RIGHT, RIGHT},
  {LEFT, RIGHT},
  {RIGHT, LEFT},
  {},
};

const vrs MINOS[9] = {
  // J
  {LEFT, LEFT, BOTH},
  {BOTH, RIGHT, RIGHT},
  // L
  {BOTH, LEFT, LEFT},
  {RIGHT, RIGHT, BOTH},
  // T
  {LEFT, BOTH, LEFT},
  {RIGHT, BOTH, RIGHT},
  // S
  {RIGHT, BOTH, LEFT},
  // Z
  {LEFT, BOTH, RIGHT},
  // O
  {BOTH, BOTH}
};

bool canMerge(RowState bot, RowState top) {
  return (bot ^ top) == (bot | top);
}

enum PushResultType {
  PUSH, POP, CHANGE, NO_CHANGE
};

struct PushResult {
  PushResult() {}
  PushResult(int a, int b) : t(a), stateNo(b) {}
  int t;
  int stateNo;
};

PushResult makePop() {
  return PushResult(POP, -1);
}

PushResult makePush(RowState bot, RowState top) {
  int stateIndex = -1;
  for (int i = 0; i < 4; i++) {
    if (bot == STATES[i][0] && top == STATES[i][1]) {
      stateIndex = i;
      break;
    }
  }
  assert(stateIndex != -1);
  return PushResult(PUSH, stateIndex);
}

PushResult makeChange(RowState bot, RowState top) {
  int stateIndex = -1;
  for (int i = 0; i < 4; i++) {
    if (bot == STATES[i][0] && top == STATES[i][1]) {
      stateIndex = i;
      break;
    }
  }
  assert(stateIndex != -1);
  return PushResult(CHANGE, stateIndex);
}

PushResult makeNoChange() {
  return PushResult(NO_CHANGE, -1);
}

PushResult push(int stateId, int minoId) {
  vrs init = STATES[stateId];
  const vrs &extension = MINOS[minoId];
  int matching = min(SZ(init), SZ(extension));
  for (int i = 0; i <= SZ(init) && i <= SZ(extension); i++) {
    bool can = true;
    for (int j = 0; j < i; j++) {
      can = can && canMerge(init[SZ(init) - i + j], extension[j]);
    }
    if (!can) {
      matching = i - 1;
      assert(matching >= 0);
      break;
    }
  }
  for (int i = 0; i < matching; i++) {
    init[SZ(init) - matching + i] = static_cast<RowState>(init[SZ(init) - matching + i] | extension[i]);
  }
  for (int i = matching; i < SZ(extension); i++) {
    init.push_back(extension[i]);
  }
  vrs ret;
  for (auto rs : init) {
    if (rs != 0 && rs != 3) {
      ret.push_back(rs);
    }
  }
  if (minoId == 8) {
    return makeNoChange();
  }
  if (stateId == 4) {
    return makePush(ret[0], ret[1]);
  }
  if (SZ(ret) == 0) {
    return makePop();
  } else if (SZ(ret) == 2) {
    return makeChange(ret[0], ret[1]);
  } else if (SZ(ret) == 4) {
    assert(ret[0] == STATES[stateId][0]);
    assert(ret[1] == STATES[stateId][1]);
    return makePush(ret[2], ret[3]);
  } else {
    assert(false);
  }
}

vector<pii> indices[256];
PushResult pushCache[5][9];

void init() {
  indices['J'] = {{0, 1}, {1, 3}};
  indices['L'] = {{2, 1}, {3, 3}};
  indices['T'] = {{4, 1}, {5, 3}};
  indices['S'] = {{6, 1}};
  indices['Z'] = {{7, 1}};
  // indices['O'] = {8};
  assert(SZ(indices['J']) == 2);
  assert(SZ(indices['L']) == 2);
  assert(SZ(indices['T']) == 2);
  assert(SZ(indices['S']) == 1);
  assert(SZ(indices['Z']) == 1);
  // assert(SZ(indices['O']) == 1);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 9; j++) {
      pushCache[i][j] = push(i, j);
    }
  }
}

#include "tetris.h"

const int MAXN = 201;

int N;
string S;
int ans[MAXN];
char dp[MAXN][MAXN][5][2];
char opt[MAXN][MAXN][5][2];

int f(int l, int r, int lastState, int mustFinish) {
  if (l > r) {
    return lastState == 4;
  }
  if (lastState == 4 && mustFinish) {
    return 0;
  }
  if (dp[l][r][lastState][mustFinish] != -1) {
    return dp[l][r][lastState][mustFinish];
  }
  if (S[l] == 'O') {
    opt[l][r][lastState][mustFinish] = 0;
    return dp[l][r][lastState][mustFinish] = f(l + 1, r, lastState, mustFinish);
  }
  int ret = 0;
  for (const auto &it : indices[S[l]]) {
    int i = it.fi;
    int j = it.se;
    int bef = ret;
    const auto &cache = pushCache[lastState][i];
    if (cache.t == PUSH) {
      // start new stack
      for (int mid = l + 1; mid <= r; mid++) {
        ret |= f(l + 1, mid, cache.stateNo, 1) & (mid < r ? f(mid + 1, r, lastState, mustFinish) : (lastState == 4));
      }
    } else if (cache.t == POP) {
      ret |= f(l + 1, r, 4, mustFinish);
    } else if (cache.t == CHANGE) {
      ret |= f(l + 1, r, cache.stateNo, mustFinish);
    } else if (cache.t == NO_CHANGE) {
      ret |= f(l + 1, r, lastState, mustFinish);
    } else {
      assert(false);
    }
    if (ret && !bef) {
      opt[l][r][lastState][mustFinish] = j;
    }
  }
  debug printf("dp[%d][%d][%d][%d] = %d\n", l, r, lastState, mustFinish, ret);
  return dp[l][r][lastState][mustFinish] = ret;
}

void backtrack(int l, int r, int lastState, int mustFinish) {
  debug printf("backtrack %d %d %d %d\n", l, r, lastState, mustFinish);
  if (l > r) {
    assert(lastState == 4);
    return;
  }
  if (lastState == 4 && mustFinish) {
    assert(false);
  }
  assert(dp[l][r][lastState][mustFinish]);
  ans[l] = opt[l][r][lastState][mustFinish];
  if (S[l] == 'O') {
    backtrack(l + 1, r, lastState, mustFinish);
    return;
  }
  for (const auto &it : indices[S[l]]) {
    int i = it.fi;
    int j = it.se;
    if (j != opt[l][r][lastState][mustFinish]) {
      continue;
    }
    const auto &cache = pushCache[lastState][i];
    if (cache.t == PUSH) {
      // start new stack
      for (int mid = l + 1; mid <= r; mid++) {
        if (f(l + 1, mid, cache.stateNo, 1) && (mid < r ? f(mid + 1, r, lastState, mustFinish) : (lastState == 4))) {
          backtrack(l + 1, mid, cache.stateNo, 1);
          if (mid < r) {
            backtrack(mid + 1, r, lastState, mustFinish);
          } else {
            assert(lastState == 4);
          }
          return;
        }
      }
    } else if (cache.t == POP) {
      backtrack(l + 1, r, 4, mustFinish);
      return;
    } else if (cache.t == CHANGE) {
      backtrack(l + 1, r, cache.stateNo, mustFinish);
      return;
    } else if (cache.t == NO_CHANGE) {
      backtrack(l + 1, r, lastState, mustFinish);
      return;
    } else {
      assert(false);
    }
  }
  assert(opt[l][r][lastState][mustFinish] != -1);
  assert(false);
}

vector<int> arrangeTetrominoes(int N, string S, int Q) {
  ::N = N;
  ::S = S;
  memset(opt, -1, sizeof(opt));
  memset(dp, -1, sizeof(dp));
  init();
  if (f(0, N - 1, 4, 0)) {
    // backtrack(0, N - 1, 4, 0);
    return vi(ans, ans + N);
  } else {
    return vi();
  }
}
