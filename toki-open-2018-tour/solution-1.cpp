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
int dp[400][400];
int ans;

inline int simulate() {
	dp[n][n] = 0;

	for (int i=n; i>=1; i--) 
		for (int j=n; j>=1; j--)  {
			if (i == n and j == n) continue;
			dp[i][j] = 1 + min(dp[i+1][j] , dp[i][j+1]);
			if (mat[i][j] == '.') dp[i][j] = min(dp[i][j] , 1+dp[i+1][j+1]);
		}

	return dp[1][1] ;
}

inline void swapX(int l,int r) {
	for (int i=1; i<=n; i++) swap(mat[l][i],mat[r][i]);
}

inline void swapY(int l,int r) {
	for (int i=1; i<=n; i++) swap(mat[i][l],mat[i][r]);
}

inline void bruteY(int p) {
	if (p > n) {
		ans = min(ans,simulate());
		return;
	}
	
	R(i,p,n) {
		swapY(p,i);
		bruteY(p+1);
		swapY(p,i);
	}
}

inline void bruteX(int p) {
	if (p > n) return bruteY(1);
	R(i,p,n) {
		swapX(p,i);
		bruteX(p+1);
		swapX(p,i);
	}
}

// int main() {
int getShortestTour(int N, std::vector<std::string> S) {
	// cin >> n;
	n = N;
	ans = 2*(n-1);
	// R(i,1,n) R(j,1,n) cin >> mat[i][j];
	R(i,1,n) R(j,1,n) mat[i][j] = S[i - 1][j - 1];
	R(i,0,n+1) R(j,0,n+1) dp[i][j] = 2*n;
	bruteX(1);
	// cout << ans << endl;
	return ans;
}