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
	
	int ans = 2000000000;
	for (int i = 0; i < (1 << N); i++) {
		vector<int> first_gr, second_gr;
		for (int j = 0; j < N; j++) {
			if (i & (1 << j))
				first_gr.push_back(j);
			else
				second_gr.push_back(j);
		}
		
		int tmp = 0;
		for (int j = 0; j < first_gr.size(); j++) {
			for (int k = j + 1; k < first_gr.size(); k++) {
				int x = first_gr[j], y = first_gr[k];
				tmp = max(tmp, dist(A[x], A[y]));
			}
		}
		for (int j = 0; j < second_gr.size(); j++) {
			for (int k = j + 1; k < second_gr.size(); k++) {
				int x = second_gr[j], y = second_gr[k];
				tmp = max(tmp, dist(A[x], A[y]));
			}
		}
		
		ans = min(ans, tmp);
	}
	
	return ans;
}
