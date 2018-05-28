#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000000;
const int MAXM = 300000;
const int MAXQ = 300000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, K, M, Q;
  vector<int> A;
  vector<int> L, R;
  vector<int> result;

  void InputFormat() {
    LINE(N, K, M, Q);
    LINE(A % SIZE(M));
    LINES(L, R) % SIZE(Q);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= K && K <= N && N <= MAXN);
    CONS(1 <= M && M <= min(N, MAXM));
    CONS(1 <= Q && Q <= MAXQ);
    CONS(eachElementBetween(A, 1, N));
    CONS(increasing(A));
    CONS(eachElementBetween(L, 1, N));
    CONS(eachElementBetween(R, 1, N));
    CONS(eachElementNotMoreThan(L, R));
  }

  void Subtask1() {
    Points(15);
    CONS(N <= 5000);
  }

  void Subtask2() {
    Points(14);
    CONS(M <= 5000);
  }

  void Subtask3() {
    Points(23);
    CONS(N <= 300000);
  }

  void Subtask4() {
    Points(13);
    CONS(K == 1);
  }

  void Subtask5() {
    Points(13);
    CONS(Q == 1);
  }

  void Subtask6() {
    Points(22);
  }

private:
  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int it : A) {
      if (it < lo || it > hi) {
        return false;
      }
    }
    return true;
  }

  bool increasing(const vector<int> &A) {
    for (int i = 1; i < A.size(); ++i) {
      if (A[i - 1] >= A[i]) {
        return false;
      }
    }
    return true;
  }

  bool eachElementNotMoreThan(const vector<int> &L, const vector<int> &R) {
    assert(L.size() == R.size());
    for (int i = 0; i < L.size(); ++i) {
      if (L[i] > R[i]) {
        return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({1, 2, 3, 6});
    Input({"11 3 5 3", "3 4 6 8 9", "1 11", "5 5", "5 6"});
  }

  void BeforeTestCase() {
    A.clear();
    L.clear();
    R.clear();
  }

  void TestGroup1() {
    Subtasks({1, 2, 3, 4, 5, 6});
    // 1 <= K <= 1
    // 1 <= Q <= 1
    // 1 <= N <= 5,000
    // 1 <= M <= 5,000

    generateCommonCases(1, 5000, 1, 5000, 1, 1, 1, 1);
  }

  void TestGroup2() {
    Subtasks({2, 3, 4, 5, 6});
    // 1 <= K <= 1
    // 1 <= Q <= 1
    // 5,001 <= N <= 300,000
    // 1 <= M <= 5,000

    generateCommonCases(5001, 300000, 1, 5000, 1, 1, 1, 1);
  }

  void TestGroup3() {
    Subtasks({2, 4, 5, 6});
    // 1 <= K <= 1
    // 1 <= Q <= 1
    // 300,001 <= N <= 1,000,000,000
    // 1 <= M <= 5,000

    generateCommonCases(300001, MAXN, 1, 5000, 1, 1, 1, 1);
  }

  void TestGroup4() {
    Subtasks({3, 4, 5, 6});
    // 1 <= K <= 1
    // 1 <= Q <= 1
    // 5,001 <= N <= 300,000
    // 5,001 <= M <= 300,000

    generateCommonCases(5001, 300000, 5001, MAXM, 1, 1, 1, 1);
  }

  void TestGroup5() {
    Subtasks({4, 5, 6});
    // 1 <= K <= 1
    // 1 <= Q <= 1
    // 300,001 <= N <= 1,000,000,000
    // 5,001 <= M <= 300,000

    generateCommonCases(300001, MAXN, 5001, MAXM, 1, 1, 1, 1);
  }

  void TestGroup6() {
    Subtasks({1, 2, 3, 4, 6});
    // 1 <= K <= 1
    // 2 <= Q <= 300,000
    // 1 <= N <= 5,000
    // 1 <= M <= 5,000

    generateCommonCases(1, 5000, 1, 5000, 1, 1, 2, MAXQ);
  }

  void TestGroup7() {
    Subtasks({2, 3, 4, 6});
    // 1 <= K <= 1
    // 2 <= Q <= 300,000
    // 5.001 <= N <= 300,000
    // 1 <= M <= 5,000

    generateCommonCases(5001, 300000, 1, 5000, 1, 1, 2, MAXQ);
  }

  void TestGroup8() {
    Subtasks({2, 4, 6});
    // 1 <= K <= 1
    // 2 <= Q <= 300,000
    // 300,001 <= N <= 1,000,000,000
    // 1 <= M <= 5,000

    generateCommonCases(300001, MAXN, 1, 5000, 1, 1, 2, MAXQ);
  }

  void TestGroup9() {
    Subtasks({3, 4, 6});
    // 1 <= K <= 1
    // 2 <= Q <= 300,000
    // 5,001 <= N <= 300,000
    // 5,001 <= M <= 300,000

    generateCommonCases(5001, 300000, 5001, MAXM, 1, 1, 2, MAXQ);
  }

  void TestGroup10() {
    Subtasks({4, 6});
    // 1 <= K <= 1
    // 2 <= Q <= 300,000
    // 300,001 <= N <= 1,000,000,000
    // 5,001 <= M <= 300,000

    generateCommonCases(300001, MAXN, 5001, MAXM, 1, 1, 2, MAXQ, true);
  }

  void TestGroup11() {
    Subtasks({1, 2, 3, 5, 6});
    // 2 <= K <= N
    // 1 <= Q <= 1
    // 2 <= N <= 5,000
    // 1 <= M <= 5,000

    generateCommonCases(2, 5000, 1, 5000, 2, 5000, 1, 1);
  }

  void TestGroup12() {
    Subtasks({2, 3, 5, 6});
    // 2 <= K <= N
    // 1 <= Q <= 1
    // 5,001 <= N <= 300,000
    // 1 <= M <= 5,000

    generateCommonCases(5001, 300000, 1, 5000, 2, 300000, 1, 1);
  }

  void TestGroup13() {
    Subtasks({2, 5, 6});
    // 2 <= K <= N
    // 1 <= Q <= 1
    // 300,001 <= N <= 1,000,000,000
    // 1 <= M <= 5,000

    generateCommonCases(300001, MAXN, 1, 5000, 2, MAXN, 1, 1);
  }

  void TestGroup14() {
    Subtasks({3, 5, 6});
    // 2 <= K <= N
    // 1 <= Q <= 1
    // 5,001 <= N <= 300,000
    // 5,001 <= M <= 300,000

    generateCommonCases(5001, 300000, 5001, MAXM, 2, 300000, 1, 1);
  }

  void TestGroup15() {
    Subtasks({5, 6});
    // 2 <= K <= N
    // 1 <= Q <= 1
    // 300,001 <= N <= 1,000,000,000
    // 5,001 <= M <= 300,000

    generateCommonCases(300001, MAXN, 5001, MAXM, 2, MAXN, 1, 1, true);
  }

  void TestGroup16() {
    Subtasks({1, 2, 3, 6});
    // 2 <= K <= N
    // 2 <= Q <= 300,000
    // 2 <= N <= 5,000
    // 1 <= M <= 5,000

    generateCommonCases(2, 5000, 1, 5000, 2, 5000, 2, MAXQ, true);
  }

  void TestGroup17() {
    Subtasks({2, 3, 6});
    // 2 <= K <= N
    // 2 <= Q <= 300,000
    // 5.001 <= N <= 300,000
    // 1 <= M <= 5,000

    generateCommonCases(5001, 300000, 1, 5000, 2, 300000, 2, MAXQ);
  }

  void TestGroup18() {
    Subtasks({2, 6});
    // 2 <= K <= N
    // 2 <= Q <= 300,000
    // 300,001 <= N <= 1,000,000,000
    // 1 <= M <= 5,000

    generateCommonCases(300001, MAXN, 1, 5000, 2, MAXN, 2, MAXQ, true);
  }

  void TestGroup19() {
    Subtasks({3, 6});
    // 2 <= K <= N
    // 2 <= Q <= 300,000
    // 5,001 <= N <= 300,000
    // 5,001 <= M <= 300,000

    generateCommonCases(5001, 300000, 5001, MAXM, 2, 300000, 2, MAXQ, true);
  }

  void TestGroup20() {
    Subtasks({6});
    // 2 <= K <= N
    // 2 <= Q <= 300,000
    // 300,001 <= N <= 1,000,000,000
    // 5,001 <= M <= 300,000

    generateCommonCases(300001, MAXN, 5001, MAXM, 2, MAXN, 2, MAXQ, true);
  }

private:
  void generateCommonCases(int minN,
                           int maxN,
                           int minM,
                           int maxM,
                           int minK,
                           int maxK,
                           int minQ,
                           int maxQ,
                           bool is_important_testgroup = false) {
    CASE(N = minN, M = minM, K = minK, Q = minQ,
         randomHoles(), randomQueries());

    vector<function<void()>> holes_generator = {randomHoles,
                                                consecutiveHoles};
    vector<function<void()>> queries_generator = {randomQueries,
                                                  randomQueriesCorners};

    if (!is_important_testgroup) {
      holes_generator = {randomHoles};
      queries_generator = {randomQueries};
    }

    for (int i = 0; i < 1; ++i) {
      for (auto query_generator : queries_generator) {
        for (auto hole_generator : holes_generator) {
          int _N, _M, _Q, _K;

          {
            _N = maxN,
            _M = maxM;
            _Q = maxQ;
            if (max(1, minK) <= min(_N / _M, maxK)) {
              _K = rnd.nextInt(max(1, minK), min(_N / _M, maxK));
              CASE(N = _N, M = _M, K = _K, Q = _Q,
                   hole_generator(), query_generator());
            }
          }

          {
            _N = maxN;
            _M = maxM;
            _Q = maxQ;
            if (max(1, minK) <= min(_N, maxK)) {
              _K = rnd.nextInt(max(1, minK), min(_N, maxK));
              CASE(N = _N, M = _M, K = _K, Q = _Q,
                   hole_generator(), query_generator());
            } 
          }
          
          {
            _N = rnd.nextInt(minN, maxN);
            _M = rnd.nextInt(minM, min(_N, maxM));
            _Q = rnd.nextInt(minQ, maxQ);
            if (max(1, minK) <= min(_N / _M, maxK)) {
              _K = rnd.nextInt(max(1, minK), min(_N / _M, maxK));
              CASE(N = _N, M = _M, K = _K, Q = _Q,
                   hole_generator(), query_generator());
            }
          }
          
          {
            _N = rnd.nextInt(minN, maxN);
            _M = rnd.nextInt(minM, min(_N, maxM));
            _Q = rnd.nextInt(minQ, maxQ);
            if (max(1, minK) <= min(_N, maxK)) {
              _K = rnd.nextInt(max(1, minK), min(_N, maxK));
              CASE(N = _N, M = _M, K = _K, Q = _Q,
                   hole_generator(), query_generator());
            }
          }
        }
      }
    }
    if (maxM > minN && minK <= 2 && 2 <= maxK) {
      CASE(N = maxM, M = maxM / 2, K = 2, Q = maxQ,
           randomHoles(), randomQueriesCorners());
    }
  }

  function<void()> consecutiveHoles = [&]() {
    int x = rnd.nextInt(1, N - M + 1);
    for (int i = 0; i < M; ++i) {
      A.push_back(x + i);
    }
  };

  function<void()> randomHoles = [&]() {
    if (2 * M < N) {
      unordered_set<int> holes;
      for (int i = 0; i < M; ++i) {
        int hole = -1;
        do {
          hole = rnd.nextInt(1, N);
        } while (holes.count(hole));
        holes.insert(hole);
        A.push_back(hole);
      }
      sort(A.begin(), A.end());
    } else {
      vector<int> holes(N, 0);
      for (int i = 0; i < M; ++i) {
        holes[i] = 1;
      }
      rnd.shuffle(holes.begin(), holes.end());
      for (int i = 0; i < N; ++i) {
        if (holes[i] == 1) {
          A.push_back(i + 1);
        }
      }
    }
  };

  function<void()> randomQueries = [&]() {
    for (int i = 0; i < Q; ++i) {
      int l = rnd.nextInt(1, N);
      int r = rnd.nextInt(0, N);
      if (r == 0) r = l;
      else if (r < l) swap(l, r);
      L.push_back(l);
      R.push_back(r);
    }
  };

  function<void()> randomQueriesCorners = [&]() {
    int range = rnd.nextInt(1, 5);
    for (int i = 0; i < Q; ++i) {
      int l = rnd.nextInt(1, min(range, N));
      int r = rnd.nextInt(max(l, N - range + 1), N);
      if (rnd.nextInt(0, 1)) {
        l = min(r, A[rnd.nextInt(0, min(range - 1, M - 1))]);
      }
      if (rnd.nextInt(0, 1)) {
        r = max(l, A[rnd.nextInt(max(0, M - range), M - 1)]); 
      }
      L.push_back(l);
      R.push_back(r);
    }
  };
};
