#include "tetris.h"

#include <bits/stdc++.h>
using namespace std;

const int INVALID_STATE = -1;

bool valid(char piece_shape, int rotation) {
  if (piece_shape == 'O') {
    return rotation == 0 || rotation == 1 || rotation == 2 || rotation == 3;
  } else if (piece_shape == 'T') {
    return rotation == 1 || rotation == 3;
  } else if (piece_shape == 'S' || piece_shape == 'Z') {
    return rotation == 1 || rotation == 3;
  } else if (piece_shape == 'J' || piece_shape == 'L') {
    return rotation == 1 || rotation == 3;
  } else {
    return false;
  }
}

vector<vector<bool>> getPiece(char piece_shape, int rotation) {
  vector<vector<bool>> piece;
  if (piece_shape == 'O') {
    if (rotation == 0 || rotation == 1 ||
        rotation == 2 || rotation == 3) {
      piece = {{0, 0},
               {1, 1},
               {1, 1}};
    } else {
      assert(false);
    }
  } else if (piece_shape == 'T') {
    if (rotation == 1) {
      piece = {{1, 0},
               {1, 1},
               {1, 0}};
    } else if (rotation == 3) {
      piece = {{0, 1},
               {1, 1},
               {0, 1}};
    } else {
      assert(false);
    }
  } else if (piece_shape == 'S') {
    if (rotation == 1 || rotation == 3) {
      piece = {{1, 0},
               {1, 1},
               {0, 1}};
    } else {
      assert(false);
    }
  } else if (piece_shape == 'Z') {
    if (rotation == 1 || rotation == 3) {
      piece = {{0, 1},
               {1, 1},
               {1, 0}};
    } else {
      assert(false);
    }
  } else if (piece_shape == 'J') {
    if (rotation == 1) {
      piece = {{1, 1},
               {1, 0},
               {1, 0}};
    } else if (rotation == 3) {
      piece = {{0, 1},
               {0, 1},
               {1, 1}};
    } else {
      assert(false);
    }
  } else if (piece_shape == 'L') {
    if (rotation == 1) {
      piece = {{1, 0},
               {1, 0},
               {1, 1}};
    } else if (rotation == 3) {
      piece = {{1, 1},
               {0, 1},
               {0, 1}};
    } else {
      assert(false);
    }
  } else {
    assert(false);
  }
  return piece;
}

int getFinalState(char piece_shape, int rotation, int origin_state) {
  if (!valid(piece_shape, rotation)) {
    return INVALID_STATE;
  }
  vector<vector<bool>> grid(10, vector<bool>(2, 0));
  grid[grid.size() - 1][0] = grid[grid.size() - 1][1] = 1;
  int dx[] = {2, 2, 3, 3};
  int dy[] = {0, 1, 0, 1};
  for (int i = 0; i < 4; ++i) {
    if (origin_state & (1 << i)) {
      grid[grid.size() - dx[i]][dy[i]] = 1;
    }
  }
  vector<vector<bool>> piece = getPiece(piece_shape, rotation);
  int put_piece = 0;
  for (int j = 0; j < grid.size(); ++j) {
    bool can_put = true;
    for (int k = 0; k < piece.size(); ++k) {
      for (int l = 0; l < piece[k].size(); ++l) {
        if (piece[k][l] && grid[j + k][l]) {
          can_put = false;
        }
      }
    }
    if (!can_put) {
      break;
    } else {
      put_piece = j;
    }
  }
  for (int k = 0; k < piece.size(); ++k) {
    for (int l = 0; l < piece[k].size(); ++l) {
      if (piece[k][l]) {
        grid[put_piece + k][l] = 1;
      }
    }
  }
  for (int j = 0; j < grid.size() - 1; ++j) {
    if (grid[j][0] && grid[j][1]) {
      grid.erase(grid.begin() + j);
      --j;
    }
  }
  assert(grid.size() >= 3);
  for (int i = 0; i < grid.size() - 3; ++i) {
    if (grid[i][0] || grid[i][1]) {
      return INVALID_STATE;
    }
  }
  int final_state = 0;
  for (int i = 0; i < 4; ++i) {
    if (grid[grid.size() - dx[i]][dy[i]] == 1) {
      final_state |= (1 << i);
    }
  }
  return final_state;
}

vector<char> tetrominoes = {'O', 'T', 'S', 'Z', 'J', 'L'};
vector<int> valid_states = {0, 5, 9, 6, 10};
int change_state[256][5][16];
int dp[205][205][16];
const int NOT_COMPUTED = -1;
string S;

int f(int lo, int hi, int state) {
  if (lo == hi) {
    return state == 0 ? 1 : 0;
  }
  int &ret = dp[lo][hi][state];
  if (ret != NOT_COMPUTED) {
    return ret;
  }
  ret = 0;
  for (int rotation = 0; rotation < 4; ++rotation) {
    int final_state = change_state[S[lo]][rotation][state];
    if (final_state != INVALID_STATE) {
      ret |= f(lo + 1, hi, final_state);
    }
  }
  for (int i = lo + 1; i < hi; ++i) {
    ret |= f(lo, i, state) & f(i, hi, 0);
    ret |= f(lo, i, 0) & f(i, hi, state);
  }
  return ret;
}

vector<int> answer;

void backtrack(int lo, int hi, int state) {
  for (int rotation = 0; rotation < 4; ++rotation) {
    int final_state = change_state[S[lo]][rotation][state];
    if (final_state != INVALID_STATE && f(lo + 1, hi, final_state)) {
      answer[lo] = rotation;
      backtrack(lo + 1, hi, final_state);
      return;
    }
  }
  for (int i = lo + 1; i < hi; ++i) {
    if (f(lo, i, state) & f(i, hi, 0)) {
      backtrack(lo, i, state);
      backtrack(i, hi, 0);
      return;
    }
    if (f(lo, i, 0) & f(i, hi, state)) {
      backtrack(lo, i, 0);
      backtrack(i, hi, state);
      return;
    }
  }
}

std::vector<int> arrangeTetrominoes(int N, std::string S, int Q) {
  for (char tetromino : tetrominoes) {
    for (int rotation = 0; rotation < 4; ++rotation) {
      for (int valid_state : valid_states) {
        change_state[tetromino][rotation][valid_state] =
            getFinalState(tetromino, rotation, valid_state);
      }
    }
  }
  assert(NOT_COMPUTED == -1);
  memset(dp, NOT_COMPUTED, sizeof(dp));
  ::S = S;
  if (f(0, N, 0) != 1) {
    return {};
  }
  answer.resize(N);
  backtrack(0, N, 0);
  return answer;
}
