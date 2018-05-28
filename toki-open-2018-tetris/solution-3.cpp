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
  // cout << "><><>< " << pushCache[pushCache[4][6].stateNo][7].stateNo << endl;
}

int N;
string S;
vi states;
vi ans;
vi curMove;

void go(int pos) {
  if (pos >= N) {
    if (states.empty()) {
      ans = curMove;
    }
    return;
  }
  if (S[pos] == 'O') {
    curMove[pos] = 0;
    go(pos + 1);
  }
  for (const pii &it : indices[S[pos]]) {
    int i = it.fi;
    int j = it.se;
    assert(j > 0);
    if (states.empty()) {
      states.push_back(pushCache[4][i].stateNo);
      curMove[pos] = j;
      go(pos + 1);
      states.pop_back();
    } else {
      const auto &pr = pushCache[states.back()][i];
      if (pr.t == PUSH) {
        states.push_back(pr.stateNo);
        curMove[pos] = j;
        go(pos + 1);
        states.pop_back();
      } else if (pr.t == POP) {
        int old = states.back();
        states.pop_back();
        curMove[pos] = j;
        go(pos + 1);
        states.push_back(old);
      } else if (pr.t == CHANGE) {
        int old = states.back();
        states.back() = pr.stateNo;
        curMove[pos] = j;
        go(pos + 1);
        states.back() = old;
      } else if (pr.t == NO_CHANGE) {
        curMove[pos] = j;
        go(pos + 1);
      } else { cout << "!!!!!! " << pr.t << endl; assert(false); }
    }
    if (!ans.empty()) {
      break;
    }
  }
}

#include "tetris.h"

vector<int> arrangeTetrominoes(int N, string S, int Q) {
  init();
  ::N = N;
  ::S = S;
  curMove.resize(N);
  go(0);
  return ans;
}

