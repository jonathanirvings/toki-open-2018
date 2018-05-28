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
int dp[20][300111];

// int main() {
int getShortestTour(int N, std::vector<std::string> S) {
	// cin >> n;
	n = N;
	R(i,0,n-1) R(j,0,(1<<n)-1) dp[i][j] = -1;

	R(i,0,n-1) R(j,0,n-1) {
		// cin >> mat[i][j];
		mat[i][j] = S[i][j];
		if (mat[i][j] == '.') v[i].push_back(j);
	}

	Re(p,n,0) R(mask,0,(1<<n)-1) {
		if (p >= n) {
			dp[p][mask] = 0;
		}
		else {
			dp[p][mask] = dp[p+1][mask]+2;
			for (int i : v[p]) if (((1<<i) & mask) == 0) {
				dp[p][mask] = min(dp[p][mask], dp[p+1][mask|(1<<i)] + 1);
			}
		}
	}

	int ans = dp[0][0];
	
	// if (ans == n) cout << ans - 1 << endl;
	// else cout << ans - 2 << endl;
	if (ans == n) return ans - 1;
	else return ans - 2;
}
