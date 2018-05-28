#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
	int M, N, K;
	vector<int> C, D;
	
	void InputFormat() {
		LINE(M, N, K);
		LINES(C, D) % SIZE(K);
	}

	void GradingConfig() {
		TimeLimit(2);
	}

	void StyleConfig() {
		BatchEvaluator();
	}

	void Constraints() {
		CONS(1 <= M && M <= 1000000000);
		CONS(1 <= N && N <= 1000000000);
		CONS(0 <= K && K <= min((long long)1e5, 1ll * M * N));
		CONS(eachElementBetween(C, 1, M));
		CONS(eachElementBetween(D, 1, N));
		CONS(eachPairUnique(C, D));
	}

	void Subtask1() {
		Points(11);

		CONS(M <= 4);
		CONS(N <= 4);
	}

	void Subtask2() {
		Points(15);

		CONS(M <= 6);
		CONS(N <= 6);
	}

	void Subtask3() {
		Points(17);

		CONS(M <= 500);
		CONS(N <= 500);
	}

	void Subtask4() {
		Points(26);

		CONS(M <= 4000);
		CONS(N <= 4000);
	}

	void Subtask5() {
		Points(31);
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

	bool eachPairUnique(vector<int> a, vector<int> b) {
		set<pair<int,int>> seen;
		for (int i = 0 ; i < a.size() ; i++) {
			if (seen.count({a[i], b[i]})) {
				return false;
			}
			seen.insert({a[i], b[i]});
		}
		return true;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({1, 2, 3, 4, 5});

		Input({"4 2 0"});
	}

	void SampleTestCase2() {
		Subtasks({3, 4, 5});

		Input({"1 113 0"});
	}

	void SampleTestCase3() {
		Subtasks({3, 4, 5});

		Input({"200 500 2", "13 1", "111 300"});
	}

	void BeforeTestCase() {
		C.clear();
		D.clear();
	}

	// 1 <= M <= 4, 1 <= N <= 4
	void TestGroup1() {
		Subtasks({1, 2, 3, 4, 5});

		CASE(M = 1, N = 1, K = 0);
		CASE(M = 4, N = 4, K = 0);
		CASE(M = 4, N = 4, K = 2, randomDistinctPairArray(M, N, K));
		
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				CASE(M = i,
					 N = j,
					 K = rnd.nextInt(0, min(M*N/2, 4)),
					 randomDistinctPairArray(M, N, K));
		
		generateCommonCase(1, 4, 1, 4);
	}
	
	// 1 <= M <= 6, 1 <= N <= 6
	void TestGroup2() {
		Subtasks({2, 3, 4, 5});

		CASE(M = 6, N = 6, K = 0);
		CASE(M = 6, N = 6, K = 3, randomDistinctPairArray(M, N, K));
		
		for (int i = 1; i <= 6; i++)
			for (int j = 1; j <= 6; j++)
				if (i > 4 || j > 4)
					CASE(M = i,
						 N = j,
						 K = rnd.nextInt(0, min(M*N/2, 6)),
						 randomDistinctPairArray(M, N, K));

		generateCommonCase(1, 6, 5, 6);
		generateCommonCase(5, 6, 1, 6);
	}

	// 1 <= M <= 500, 1 <= N <= 500
	void TestGroup3() {
		Subtasks({3, 4, 5});

		generateCommonCase(1, 500, 7, 500);
		generateCommonCase(7, 500, 1, 500);
	}

	// 1 <= M <= 4000, 1 <= N <= 4000
	void TestGroup4() {
		Subtasks({4, 5});

		generateCommonCase(1, 4000, 501, 4000);
		generateCommonCase(501, 4000, 1, 4000);
	}

	// 1 <= M <= 1e9, 1 <= N <= 1e9
	void TestGroup5() {
		Subtasks({5});

		generateCommonCase(1, 1e9, 4001, 1e9);
		generateCommonCase(4001, 1e9, 1, 1e9);
	}

private:
	void generateCommonCase(int minM, int maxM, int minN, int maxN) {
		// max test, K = 0
		CASE(M = maxM, 
			 N = maxN, 
			 K = 0,
			 randomDistinctPairArray(M, N, K));

		// max test, K gede
		CASE(M = maxM, 
			 N = maxN,
			 K = max(0ll, min((long long)1e5, 1ll * M * N) - rnd.nextInt(10)), 
			 randomDistinctPairArray(M, N, K));

		// random case, K = 0
		for (int i = 0 ; i < 4 ; i++) {
			CASE(M = rnd.nextInt(minM, maxM), 
				 N = rnd.nextInt(minN, maxN),
				 K = 0, 
				 randomDistinctPairArray(M, N, K));
		}

		// random case, K random
		for (int i = 0 ; i < 4 ; i++) {
			CASE(M = rnd.nextInt(minM, maxM), 
				 N = rnd.nextInt(minN, maxN),
				 K = rnd.nextInt(0, min((long long)1e5, 1ll * M * N)), 
				 randomDistinctPairArray(M, N, K));
		}

		// big case, K kecil
		for (int i = 0 ; i < 4 ; i++) {
			CASE(M = rnd.nextInt(max(minM, maxM-50), maxM), 
				 N = rnd.nextInt(max(minN, maxN-50), maxN),
				 K = rnd.nextInt(0, min(100ll, 1ll * M * N)), 
				 randomDistinctPairArray(M, N, K));
		}

		// big case, K random
		for (int i = 0 ; i < 4 ; i++) {
			CASE(M = rnd.nextInt(max(minM, maxM-50), maxM), 
				 N = rnd.nextInt(max(minN, maxN-50), maxN),
				 K = rnd.nextInt(0, min((long long)1e5, 1ll * M * N)), 
				 randomDistinctPairArray(M, N, K));
		}
	}

	void randomDistinctPairArray(int m, int n, int k) {
		set<pair<int,int>> seen;

		for (int i = 0 ; i < k ; i++) {
			int a, b;
			do {
				a = rnd.nextInt(1, m);
				b = rnd.nextInt(1, n);
			} while(seen.count({a, b}));
			seen.insert({a, b});
			C.push_back(a);
			D.push_back(b);
		}
	}
};

