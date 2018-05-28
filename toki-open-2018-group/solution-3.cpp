#include "group.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> point;
vector<point> A;
vector<int> edge[2007];
int color[2007];

int dist(point A, point B) {
	return abs(A.first - B.first) + abs(A.second - B.second);
}

void DFS(int pos, int col) {
	color[pos] = col;
	for (int i = 0; i < edge[pos].size(); i++) {
		if (color[edge[pos][i]] == -1) DFS(edge[pos][i], 1 - col);
	}
}

bool isBipartite(int N) {
	for (int i = 0; i < N; i++) color[i] = -1;
	for (int i = 0; i < N; i++) if (color[i] == -1) DFS(i, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < edge[i].size(); j++) {
			if (color[i] == color[edge[i][j]]) return false;
		}
	}
	return true;
}

int getMinimumDelay(int N, vector<int> X, vector<int> Y) {
	for (int i = 0; i < N; i++) {
		A.push_back(point(X[i], Y[i]));
	}
	
	long long base = 0;
	long long top = 2000000000;
	while (base != top) {
		long long mid = (base + top) / 2;
		for (int i = 0; i < N; i++) edge[i].clear();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (dist(A[i], A[j]) > mid) edge[i].push_back(j);
			}
		}
		if (isBipartite(N)) top = mid; else base = mid + 1;
	}	
	return top;
}
