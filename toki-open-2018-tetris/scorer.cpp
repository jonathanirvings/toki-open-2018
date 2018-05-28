#include <bits/stdc++.h>
using namespace std;

vector<string> readFile(ifstream &stream) {
  vector<string> res;
  string s;
  while (getline(stream, s)) {
    res.push_back(s);
  }
  return res;
}

void wrongAnswer() {
  puts("WA");
  exit(0);
}

void accepted() {
  puts("AC");
  exit(0);
}

vector<vector<bool>> getPiece(char piece_shape, string rotation) {
  vector<vector<bool>> piece;
  if (piece_shape == 'O') {
    if (rotation == "0" || rotation == "1" ||
        rotation == "2" || rotation == "3") {
      piece = {{0, 0},
               {1, 1},
               {1, 1}};
    } else {
      wrongAnswer();
    }
  } else if (piece_shape == 'T') {
    if (rotation == "1") {
      piece = {{1, 0},
               {1, 1},
               {1, 0}};
    } else if (rotation == "3") {
      piece = {{0, 1},
               {1, 1},
               {0, 1}};
    } else {
      wrongAnswer();
    }
  } else if (piece_shape == 'S') {
    if (rotation == "1" || rotation == "3") {
      piece = {{1, 0},
               {1, 1},
               {0, 1}};
    } else {
      wrongAnswer();
    }
  } else if (piece_shape == 'Z') {
    if (rotation == "1" || rotation == "3") {
      piece = {{0, 1},
               {1, 1},
               {1, 0}};
    } else {
      wrongAnswer();
    }
  } else if (piece_shape == 'J') {
    if (rotation == "1") {
      piece = {{1, 1},
               {1, 0},
               {1, 0}};
    } else if (rotation == "3") {
      piece = {{0, 1},
               {0, 1},
               {1, 1}};
    } else {
      wrongAnswer();
    }
  } else if (piece_shape == 'L') {
    if (rotation == "1") {
      piece = {{1, 0},
               {1, 0},
               {1, 1}};
    } else if (rotation == "3") {
      piece = {{1, 1},
               {0, 1},
               {0, 1}};
    } else {
      wrongAnswer();
    }
  } else {
    assert(false);
  }
  return piece;
}

int main(int argc, char* argv[]) {
  ifstream in(argv[1]), out(argv[2]), con(argv[3]);

  int N, Q;
  string S;

  in >> N >> Q;
  in >> S;

  vector<string> output = readFile(out);
  vector<string> contestant = readFile(con);

  assert(output.size() == 1 || output.size() == N + 1);

  if (output.size() != contestant.size()) {
    wrongAnswer();
  }

  if (output[output.size() - 1] != contestant[contestant.size() - 1]) {
    // Wrong password.
    wrongAnswer();
  }

  if (output.size() == 1) {
    accepted();
  }

  if (Q == 0) {
    accepted();
  } else {
    vector<vector<bool>> grid(4 * N + 5, vector<bool>(2, 0));
    grid[grid.size() - 1][0] = grid[grid.size() - 1][1] = 1;
    for (int i = 0; i < N; ++i) {
      vector<vector<bool>> piece = getPiece(S[i], contestant[i]);
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
      assert(grid.size() > 0);
    }
    for (int i = 0; i < grid.size() - 1; ++i) {
      if (grid[i][0] || grid[i][1]) {
        wrongAnswer();
      }
    }
    accepted();
  }
}
