#include "tour.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<pii,pii> ppi;
typedef pair<LL,LL> pll;
typedef pair<string,string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<LL> vl;
typedef vector<vl> vvl;
typedef vector<string> vstr;
typedef vector<char> vc;

double EPS = 1e-9;
int INF = 2000000000;
long long INFF = 8000000000000000000LL;
double PI = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

#ifdef TESTING
  #define DEBUG fprintf(stderr,"====TESTING====\n")
  #define VALUE(x) cerr << "The value of " << #x << " is " << x << endl
  #define debug(...) fprintf(stderr, __VA_ARGS__)
#else
  #define DEBUG 
  #define VALUE(x)
  #define debug(...)
#endif

#define FOR(a,b,c) for (int (a)=(b);(a)<(c);++(a))
#define FORN(a,b,c) for (int (a)=(b);(a)<=(c);++(a))
#define FORD(a,b,c) for (int (a)=(b);(a)>=(c);--(a))
#define FORSQ(a,b,c) for (int (a)=(b);(a)*(a)<=(c);++(a))
#define FORL(a,b,c) for (LL (a)=(b);(a)<=(c);++(a))
#define FORLSQ(a,b,c) for (int (a)=(b);(LL)(a)*(LL)(a)<=(c);++(a))
#define FORC(a,b,c) for (char (a)=(b);(a)<=(c);++(a))
#define REP(i,n) FOR(i,0,n)
#define REPN(i,n) FORN(i,1,n)
#define REPD(i,n) FORD(i,n,1)
#define MAX(a,b) a = max(a,b)
#define MIN(a,b) a = min(a,b)
#define SQR(x) ((x) * (x))
#define RESET(a,b) memset(a,b,sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ALL(v) v.begin(),v.end()
#define ALLA(arr,sz) arr,arr+sz
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define SORTA(arr,sz) sort(ALLA(arr,sz))
#define REVERSEA(arr,sz) reverse(ALLA(arr,sz))
#define PERMUTE next_permutation
#define TC(t) while(t--)
#define READ(n,data) {scanf("%d",&n); REPN(i,n) scanf("%d",&data[i]);}

inline string IntToString(int a){
    char x[100];
    sprintf(x,"%d",a); string s = x;
    return s;
}

inline int StringToInt(string a){
    char x[100]; int res;
    strcpy(x,a.c_str()); sscanf(x,"%d",&res);
    return res;
}

inline string GetString(void){
  char x[1000005];
  scanf("%s",x); string s = x;
  return s;
}

inline string uppercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
  return s;
}

inline string lowercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
  return s;
}

inline void OPEN (string s) {
    freopen ((s + ".in").c_str (), "r", stdin);
    freopen ((s + ".out").c_str (), "w", stdout);
}

//end of jonathanirvings' template v2.0.0 (BETA)

class BipartiteGraph
{
  public:
  bool visited[10105];
  int with[10105],m,n;
  vector<int> adj[10105];
  bool matched[10105];

  void reset(int _m,int _n)
  {
    m = _m; n = _n;
    for (int i = 0; i < m; ++i) {
      adj[i].clear();
    }
  }
  void addEdge(int a,int b)
  {
    adj[a].push_back(b);
  }
  bool match(int x)
  {
    for (int i = 0; i < adj[x].size(); ++i) {
      int j = adj[x][i];
      if (visited[j]) continue;
      visited[j] = 1;
      if (with[j] == -1 || match(with[j])) 
      {
        with[j] = x;
        return true;
      }
    }
    return false;
  }
  void greedyPreprocessing(void) {
    srand(n);
    for (int i = 0; i < m; ++i) {
      vector<int> available;
      for (int j = 0; j < adj[i].size(); ++j) {
        if (with[adj[i][j]] == -1) {
          available.push_back(adj[i][j]);
        }
      }
      if (available.size() == 0) {
        continue;
      }
      int ambil = available[rand() % available.size()];
      matched[i] = true;
      with[ambil] = i;
    }
  }
  int countMCBM(void)
  {
    int ans = 0;
    memset(with, -1, sizeof(with));
    memset(matched, 0, sizeof(matched));
    greedyPreprocessing();
    for (int i = 0; i < m; ++i)
    {
      if (matched[i]) {
        ++ans;
        continue;
      }
      memset(visited, 0, sizeof(visited));
      if(match(i)) ++ans;
    }
    return ans;
  }
};

int n;
string s;
BipartiteGraph BG;

// int main()
// {
int getShortestTour(int N, std::vector<std::string> S) {
  // scanf("%d",&n);
  n = N;
  BG.reset(n,n);
  REP(i,n)
  {
    // s = GetString();
    s = S[i];
    REP(j,n)
    {
      if (s[j] == '.') BG.addEdge(i,j);
    }
  }
  // printf("%d\n", 2*n-2-min(n-1,BG.countMCBM()));
  // return 0;
  return 2*n-2-min(n-1,BG.countMCBM());
}
