#include <tcframe/spec.hpp>
using namespace tcframe;
using namespace std;

const int MAXN = 100000;
const int MAXCOORD = 1000000000;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N;
  vector<int> X, Y;
  int ans;

  void InputFormat() {
    LINE(N);
    LINES(X, Y) % SIZE(N);
  }

  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(eachElementBetween(X, 1, MAXCOORD));
    CONS(eachElementBetween(Y, 1, MAXCOORD));
  }

  void Subtask1() {
    Points(5);
    CONS(N <= 3);
  }

  void Subtask2() {
    Points(12);
    CONS(N <= 16);
  }

  void Subtask3() {
    Points(25);
    CONS(N <= 2000);
  }

  void Subtask4() {
    Points(15);
    CONS(eachElementEqual(X));
  }

  void Subtask5() {
    Points(43);
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

  bool eachElementEqual(const vector<int> &A) {
    for (int i = 1; i < A.size(); ++i) {
      if (A[i - 1] != A[i]) {
        return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
  void SampleTestCase1() {
    Subtasks({2, 3, 5});
    Input({"8",
		   "1 6",
			"4 9",
			"9 8",
			"12 7",
			"12 5",
			"9 4",
			"9 6",
			"6 3"});
  }

  void SampleTestCase2() {
    Subtasks({2, 3, 5});
    Input({"5",
      "1 2",
      "1 5",
      "3 4",
      "4 1",
      "4 2"});
  }

  void BeforeTestCase() {
    X.clear();
    Y.clear();
  }

  void TestGroup1() {
    Subtasks({1, 2, 3, 4, 5});
    CASE(N = 1, X={MAXCOORD}, Y={MAXCOORD});
    CASE(N = 1, X={1}, Y={1});
    CASE(N = 2, X={77, 77}, Y={321, 321}); // tumpuk
    CASE(N = 3, X={1532465, 1532465, 1532465}, Y={999999, 999999, 999999}); // tumpuk
  }

  void TestGroup2() {
    Subtasks({1, 2, 3, 5});
    buildTC(3);
  }

  void TestGroup3() {
  	Subtasks({2, 3, 5});
  	buildTC(16);
  }

  void TestGroup4() {
  	Subtasks({3, 5});
  	buildTC(2000);
  }

  void TestGroup5() {
  	Subtasks({5});
  	buildTC(100000);
  }

  void TestGroup6() {
  	Subtasks({1, 2, 3, 4, 5});
  	buildLinear(3);
  }
  
  void TestGroup7() {
  	Subtasks({2, 3, 4, 5});
  	buildLinear(16);
  }

  void TestGroup8() {
  	Subtasks({3, 4, 5});
  	buildLinear(2000);
  }

  void TestGroup9() {
  	Subtasks({4, 5});
  	buildLinear(100000);
  }

  


private:
	void buildTC(int n) {
		int low = n * 0.8;
  		CASE(genRandomPts(n), setBorder());
    	CASE(genRandomPts(n));
    	CASE(genRandomPts(n, 1, 100));
    	CASE(genRandomPts(n, 1, 10000));
    	CASE(genRandomPts(rnd.nextInt(low, n)));
    	CASE(genRandomPts(rnd.nextInt(low, n), MAXCOORD - 1000, MAXCOORD));
	}

	void buildLinear(int n) {
		int low = n * 0.8;
    	CASE(genRandomPts(n), setBorder(), linearX());
    	CASE(genRandomPts(n), linearX());
    	CASE(genRandomPts(n, 1, 100), linearX());
    	CASE(genRandomPts(n, 1, 10000), linearX());
    	CASE(genRandomPts(rnd.nextInt(low, n)), linearX());
    	CASE(genRandomPts(rnd.nextInt(low, n), MAXCOORD - 1000, MAXCOORD), linearX());
	}

    void linearX() {
      for (int i=0;i<N;i++){
      	X[i] = X[0];
      }
    }

    void setBorder() {
    	X[0] = 1; Y[0] = 1; if (N <= 1) return;
    	X[1] = MAXCOORD; Y[1] = MAXCOORD; if (N <= 2) return;
    	X[2] = 1; Y[2] = MAXCOORD; if (N <= 3) return;
    	X[3] = MAXCOORD; Y[3] = 1;
    }

	void genRandomPts(int n, int lo, int hi){
		N = n;
    	for (int i=0;i<n;i++){
    		X.push_back(rnd.nextInt(lo, hi));
    		Y.push_back(rnd.nextInt(lo, hi));
    	}
	}

	void genRandomPts(int n){
		genRandomPts(n, 1, MAXCOORD);
	}
};