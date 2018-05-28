#include "group.h"
#include <bits/stdc++.h>
using namespace std;

int getMinimumDelay(int N, vector<int> X, vector<int> Y) {
	if (N <= 2) return 0;
	
	int ans = 2000000000;
	sort(Y.begin(), Y.end());
	for (int i = 0; i < N - 1; i++) {
		ans = min(ans, max(Y[i] - Y[0], Y[N - 1] - Y[i + 1]));
	}
	return ans;
}
