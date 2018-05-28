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

void accepted(int score) {
  puts("OK");
  printf("%d\n", score);
  exit(0);
}

const vector<int> subtask_query_limits = {1000000, 4000, 3000};
const vector<function<int(int)>> subtask_score = {
  [](int queries) { return 15; },
  [](int queries) { return 35; },
  [](int queries) {
    const int WORST_SOLUTION_QUERIES = 3000;
    const int BEST_SOLUTION_QUERIES = 999;
    const int PARTIAL_SCORE = 25;
    const int FULL_SCORE = 50;
    const double EPS = 1e-9;

    if (queries < BEST_SOLUTION_QUERIES) {
      return FULL_SCORE;
    }
    return (int)floor(
        FULL_SCORE - sqrt((queries - BEST_SOLUTION_QUERIES) * 1.0
                          / (WORST_SOLUTION_QUERIES - BEST_SOLUTION_QUERIES))
        * (FULL_SCORE - PARTIAL_SCORE) + EPS);
  }
};

int convertStringToNumberOfQueries(string s) {
  const int LENGTH_LIMIT = 9;
  if (s.size() == 0 || s.size() > LENGTH_LIMIT) {
    wrongAnswer();
  }

  int number_of_queries = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] < '0' || s[i] > '9') {
      wrongAnswer();
    }
    number_of_queries = number_of_queries * 10 + s[i] - '0';
  }

  return number_of_queries;
}

int main(int argc, char* argv[]) {
  ifstream in(argv[1]), out(argv[2]), con(argv[3]);

  vector<string> output = readFile(out);
  vector<string> contestant = readFile(con);

  assert(output.size() == 3);

  if (output.size() != contestant.size()) {
    wrongAnswer();
  }

  if (output[output.size() - 1] != contestant[contestant.size() - 1]) {
    // Wrong password.
    wrongAnswer();
  }

  int number_of_queries = convertStringToNumberOfQueries(contestant[1]);

  if (number_of_queries != contestant[0].size()) {
    wrongAnswer();
  }

  assert(subtask_query_limits.size() == subtask_score.size());

  int score = 0;
  for (int i = 0; i < subtask_query_limits.size(); ++i) {
    if (number_of_queries <= subtask_query_limits[i]) {
      score += subtask_score[i](number_of_queries);
    }
  }

  accepted(score);
}
