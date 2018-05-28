#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int X, Y;

  int N = 1000, M = 1000;

  void InputFormat() {
    LINE(X, Y);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(N == 1000);
    CONS(M == 1000);
    CONS(1 <= X && X <= N);
    CONS(1 <= Y && Y <= M);
  }

  void Subtask1() {}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({1});
    
    Input({
      "2 4",
    });
  }

  void TestGroup1() {
    Subtasks({1});

    generateCases();
  }

private:
  void generateCases() {
    set<pair<int, int>> golds = {
      /* Titipan Irvin */
      {1, 1},
      {1, 2},
      {1, 500},
      {2, 1},
      {2, 2},
      {2, 500},
      {500, 1},
      {500, 2},
      {500, 500},

      /* Aji killer */
      {881, 1000}, // 1015
      {1, 659}, // 1002
      {139, 521}, // 1002
      {241, 419}, // 1002
      {419, 241}, // 1002
      {521, 139}, // 1002
      {659, 1}, // 1002

      /* Irvin killer */
      {999, 880}, // 1023
      {998, 879}, // 1022
      {1000, 839}, // 1021
      {999, 838}, // 1021
      {997, 878}, // 1021

      /* Random manusia */
      {3, 4},
      {3, 5},
      {123, 456},
      {499, 501},
      {991, 997},

      /* Random komputer */
      {rnd.nextInt(1, 1000), 1},
      {rnd.nextInt(1, 1000), 1},
      {rnd.nextInt(1, 1000), 1},
      {rnd.nextInt(1, 1000), 1000},
      {rnd.nextInt(1, 1000), 1000},
      {rnd.nextInt(1, 1000), 1000},
      {1, rnd.nextInt(1, 1000)},
      {1, rnd.nextInt(1, 1000)},
      {1, rnd.nextInt(1, 1000)},
      {1000, rnd.nextInt(1, 1000)},
      {1000, rnd.nextInt(1, 1000)},
      {1000, rnd.nextInt(1, 1000)},
      {rnd.nextInt(1, 1000), rnd.nextInt(1, 1000)},
      {rnd.nextInt(1, 1000), rnd.nextInt(1, 1000)},
      {rnd.nextInt(1, 1000), rnd.nextInt(1, 1000)},
      {rnd.nextInt(1, 1000), rnd.nextInt(1, 1000)},
      {rnd.nextInt(1, 1000), rnd.nextInt(1, 1000)},
    };

    while (golds.size() < 50) golds.insert({
      rnd.nextInt(1, 1000), rnd.nextInt(1, 1000)
    });
    
    mirror(golds);

    while (golds.size() < 200) golds.insert({
      rnd.nextInt(1, 1000), rnd.nextInt(1, 1000)
    });

    for (pair<int, int> gold: golds) {
      CASE(X = gold.first; Y = gold.second);
    }
  }
  
  void mirror(set<pair<int, int>> &golds) {
    set<pair<int, int>> res;
    
    for (pair<int, int> gold: golds) {
      int x = gold.first;
      int y = gold.second;
      
      res.insert({x, y});
      res.insert({N - x + 1, y});
      res.insert({x, M - y + 1});
      res.insert({N - x + 1, M - y + 1});
    }
    
    golds = res;
  }
};
