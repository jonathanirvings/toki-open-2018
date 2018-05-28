#include "tour.h"

#include <bits/stdc++.h>

using namespace std;

vector<int> adj[303];
bitset<303> vis;
int match[303];
// char s[303];
const char* s;

int alternating(int u)
{
	if (vis[u]) return 0;
	vis[u] = 1;
	for (int i = 0; i < adj[u].size(); ++i)
	{
		if (match[adj[u][i]] == -1 || alternating(match[adj[u][i]]))
		{
			match[adj[u][i]] = u;
			return 1;
		}
	}
	return 0;
}

// int main()
// {
int getShortestTour(int N, std::vector<std::string> S) {
	int n;
	// scanf("%d", &n);
	n = N;
	for (int i = 0; i < n; ++i)
	{
		// scanf("%s", s);
		s = S[i].c_str();
		for (int j = 0; j < n; ++j)
		{
			if (s[j] == '.')
			{
				adj[i].push_back(j);
			}
		}
		match[i] = -1;
	}
	int ans = 0;
	for (int i = 0; i < n; ++i)
	{
		vis.reset();
		ans += alternating(i);
	}
	// printf("%d\n", ans - 1 + (ans < n) * (2 * (n - ans) - 1));
	// return 0;
	return ans - 1 + (ans < n) * (2 * (n - ans) - 1);
}
