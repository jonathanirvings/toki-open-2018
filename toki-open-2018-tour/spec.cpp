// #include "tcframe/runner.hpp"
#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

// class Problem : public BaseProblem {
class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<string> input;
  int result;

  void InputFormat() {
    LINE(N);
    LINES(input) % SIZE(N);
  }

  // void OutputFormat() {
  //   LINE(result);
  // }

  void Constraints() {
    CONS(1 <= N && N <= 300);
    CONS(checkGrid());
  }

  void Subtask1() {
    Points(13);
    CONS(1 <= N && N <= 5);
    // CONS(checkGrid());
  }

  void Subtask2() {
    Points(20);
    CONS(1 <= N && N <= 8);
    // CONS(checkGrid());
  }

  void Subtask3() {
    Points(20);
    CONS(1 <= N && N <= 16);
    // CONS(checkGrid());
  }

  void Subtask4() {
    Points(47);
    // CONS(1 <= N && N <= 300);
    // CONS(checkGrid());
  }

private:

  bool checkGrid() {
    for (string in : input) {
      if (in.size() != N) {
        return false;
      }
      for (char c : in) {
        if (c != '.' && c != '*') {
          return false;
        }
      }
    }
    return true;
  }
};

// class Generator : public BaseGenerator<Problem> {
class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  // void Config() {
  //   setSlug("perjalanan-kotak");
  // }

  // void SampleTestCases() {
  //   SAMPLE_CASE({"3", "**.", ".*.", "..*"}, {1, 2, 3, 4});
  //   SAMPLE_CASE({"3", "**.", "***", "***"}, {1, 2, 3, 4});
  // }

  void SampleTestCase1() {
    Subtasks({1, 2, 3, 4});
    Input({"3", "**.", ".*.", "..*"});
  }

  void SampleTestCase2() {
    Subtasks({1, 2, 3, 4});
    Input({"3", "**.", "***", "***"});
  }

  void TestGroup1() { // 1 <= N <= 5
    // assignToSubtasks({1, 2, 3, 4});
    Subtasks({1, 2, 3, 4});

    CASE(N = 1, input = {"*"});
    CASE(N = 1, input = {"."});
    CASE(N = 2, input = {"**", "**"});
    CASE(N = 2, input = {"**", "*."});
    CASE(N = 2, input = {"**", ".."});
    CASE(N = 2, input = {"*.", ".."});
    CASE(N = 2, input = {"..", ".."});

    for (int i = 0; i < 10; ++i) {
      CASE(N = rnd.nextInt(3, 5), randomGrid(rnd.nextDouble(0, 1)));
    }

    for (int i = 0; i < 3; ++i) {
      CASE(N = rnd.nextInt(3, 5), exactlyPerfectMatch());
      CASE(N = rnd.nextInt(3, 5), oneEachRow()); 
    }

    CASE(N = 5, randomGrid(0));
    CASE(N = 5, randomGrid(0.5));
    CASE(N = 5, randomGrid(1));
    CASE(N = 5, exactlyPerfectMatch());
    CASE(N = 5, oneEachRow());
  }

  void TestGroup2() { // 6 <= N <= 8
    // assignToSubtasks({2, 3, 4});
    Subtasks({2, 3, 4});

    for (int i = 0; i < 10; ++i) {
      CASE(N = rnd.nextInt(6, 8), randomGrid(rnd.nextDouble(0, 1)));
    }

    for (int i = 0; i < 3; ++i) {
      CASE(N = rnd.nextInt(6, 8), exactlyPerfectMatch());
      CASE(N = rnd.nextInt(6, 8), oneEachRow()); 
    }

    CASE(N = 8, randomGrid(0));
    CASE(N = 8, randomGrid(0.5));
    CASE(N = 8, randomGrid(1));
    CASE(N = 8, exactlyPerfectMatch());
    CASE(N = 8, oneEachRow());
  }

  void TestGroup3() { // 9 <= N <= 16
    // assignToSubtasks({3, 4});
    Subtasks({3, 4});

    for (int i = 0; i < 10; ++i) {
      CASE(N = rnd.nextInt(9, 16), randomGrid(rnd.nextDouble(0, 1)));
      CASE(N = rnd.nextInt(9, 16), randomGrid(rnd.nextDouble(0, 0.5)));
    }

    for (int i = 0; i < 3; ++i) {
      CASE(N = rnd.nextInt(9, 16), exactlyPerfectMatch());
      CASE(N = rnd.nextInt(9, 16), oneEachRow()); 
    }

    CASE(N = 16, randomGrid(0));
    CASE(N = 16, randomGrid(0.5));
    CASE(N = 16, randomGrid(1));
    CASE(N = 16, exactlyPerfectMatch());
    CASE(N = 16, oneEachRow());
  }

  void TestGroup4() { // 17 <= N <= 300
    // assignToSubtasks({4});
    Subtasks({4});

    for (int i = 0; i < 10; ++i) {
      CASE(N = rnd.nextInt(17, 300), randomGrid(rnd.nextDouble(0, 1)));
      CASE(N = rnd.nextInt(17, 300), randomGrid(rnd.nextDouble(0, 0.25)));
    }

    for (int i = 0; i < 3; ++i) {
      CASE(N = rnd.nextInt(17, 300), exactlyPerfectMatch());
      CASE(N = rnd.nextInt(17, 300), oneEachRow()); 
    }

    CASE(N = 300, randomGrid(0));
    CASE(N = 300, randomGrid(0.5));
    CASE(N = 300, randomGrid(1));
    CASE(N = 300, exactlyPerfectMatch());
    CASE(N = 300, oneEachRow());
  }

private:
  mt19937 mersenne = mt19937(0xfafa);

  void randomGrid() {
    input.clear();
    for (int i = 0; i < N; ++i) {
      input.push_back("");
      for (int j = 0; j < N; ++j) {
        input[i] += (rnd.nextInt(0, 1) ? "." : "*");
      }
    }
  }

  void randomGrid(double probWhite) {
    input.clear();
    for (int i = 0; i < N; ++i) {
      input.push_back("");
      for (int j = 0; j < N; ++j) {
        input[i] += (rnd.nextDouble(0, 1) < probWhite ? "." : "*");
      }
    }
  }

  void exactlyPerfectMatch() {
    randomGrid(0);
    vector<int> p;
    for (int i = 0; i < N; ++i) {
      p.push_back(i);
    }
    rnd.shuffle(p.begin(), p.end());
    for (int i = 0; i < N; ++i) {
      input[i][p[i]] = '.';
    }
  }

  void oneEachRow() {
    exactlyPerfectMatch();
    for (int i = 0; i < N; ++i) {
      rnd.shuffle(input[i].begin(), input[i].end());
    }
  }

};

// int main(int argc, char* argv[]) {
//   Runner<Problem> runner(argc, argv);

//   runner.setGenerator(new Generator());
//   return runner.run();
// }
