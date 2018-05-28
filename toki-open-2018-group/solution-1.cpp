#include "group.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> point;
vector<point> A;

int dist(point A, point B) {
	return abs(A.first - B.first) + abs(A.second - B.second);
}

int getMinimumDelay(int N, vector<int> X, vector<int> Y) {
	for (int i = 0; i < N; i++) {
		A.push_back(point(X[i], Y[i]));
	}
	
	if (N <= 2) return 0;
	return min(min(dist(A[0], A[1]), dist(A[1], A[2])), dist(A[2], A[0]));
}
