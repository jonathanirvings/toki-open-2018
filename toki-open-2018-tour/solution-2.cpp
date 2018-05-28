#include "tour.h"

#include <bits/stdc++.h>

#define sz(a) int((a).size())
#define all(c) (c).begin(),(c).end()
#define uniq(c) sort(all((c))), (c).resize(unique(all((c))) - (c).begin())
#define lobo(c, x) (int) (lower_bound(all((c)), (x)) - (c).begin())
#define upbo(c, x) (int) (upper_bound(all((c)), (x)) - (c).begin())
#define R(i,a,b)  for (int i=a; i<=b; i++)
#define Re(i,a,b) for (int i=a; i>=b; i--)
#define tr(i,a) for (__typeof(a.begin()) i = a.begin(); i != a.end(); i++)
#define tes cout << "test" << endl, fflush(stdout);
#define cincout ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define print(_v) cout << #_v << " : "; for (auto _i : _v) cout << _i <<", "; cout << endl;

#define pb push_back
#define mt make_tuple
#define mp make_pair
#define x first
#define y second

#define MOD 1000000007
#define INF 1000111222
#define EPS 1e-9
#define endl "\n"

using namespace std;

typedef long long int64;
typedef pair<int,int> ii;

int n;
char mat[400][400];
vector<int> v[400];
int ans,cur;
set<pair<int,set<int>>> memo;
set<int> mem;

inline void brute(int p) {
	if (p > n) { ans = min(ans,cur); return; }
	if (cur > ans) return;
	// if (memo.count(make_pair(p,mem))) return;
	memo.insert(make_pair(p,mem));

	for (int i : v[p]) if (mem.count(i) == 0) {
		mem.insert(i);
		cur += 1; brute(p+1); cur -= 1;
		mem.erase(i);
	}

	cur += 2; brute(p+1); cur -= 2;
}

// int main() {
int getShortestTour(int N, std::vector<std::string> S) {
	// cin >> n;
	n = N;
	ans = 2*n;

	R(i,1,n) R(j,1,n) {
		// cin >> mat[i][j];
		mat[i][j] = S[i - 1][j - 1];
		if (mat[i][j] == '.') v[i].push_back(j);
	}

	cur = 0;
	brute(1);
	
	// if (ans == n) cout << ans - 1 << endl;
	// else cout << ans - 2 << endl;
	if (ans == n) return ans - 1;
	else return ans - 2;
}
