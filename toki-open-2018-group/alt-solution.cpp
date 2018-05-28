#include "group.h"

#include <algorithm>
#include <vector>

using namespace std;

const int INF = 2000000000;

int getDelay(int N, vector<int> &X, vector<int> &Y, int op1(int x, int y), int op2(int x, int y)) {
  vector<pair<int, int>> a, b;
  vector<bool> used(N);

  for (int i=0; i<N; i++) {
    a.push_back({op1(X[i], Y[i]), i});
    b.push_back({op2(X[i], Y[i]), i});
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  int maks1 = max(a.back().first - a[0].first, b.back().first - b[0].first);
  int maks2 = 0;
  int ret = max(maks1, maks2);
  pair<int, int> minmax1, minmax2 = minmax1 = {INF, -INF};
  for (int i=1; i<N; i++) {
    int take;
    if (a.back().first - a[0].first < b.back().first - b[0].first) {
      take = b.back().second;
    } else {
      take = a.back().second;
    }

    used[take] = true;
    while (used[a.back().second]) a.pop_back();
    while (used[b.back().second]) b.pop_back();

    int tmp = op1(X[take], Y[take]);
    minmax1.first = min(minmax1.first, tmp);
    minmax1.second = max(minmax1.second, tmp);

    tmp = op2(X[take], Y[take]);
    minmax2.first = min(minmax2.first, tmp);
    minmax2.second = max(minmax2.second, tmp);

    maks1 = max(a.back().first - a[0].first, b.back().first - b[0].first);
    maks2 = max(minmax1.second - minmax1.first, minmax2.second - minmax2.first);
    ret = min(ret, max(maks1, maks2));
  }

  return ret;
}

int getMinimumDelay(int N, std::vector<int> X, std::vector<int> Y) {
  return min(
    getDelay(N, X, Y, [](int x, int y) { return x + y; }, [](int x, int y) { return x - y; }),
    getDelay(N, X, Y, [](int x, int y) { return -x - y; }, [](int x, int y) { return x - y; })
  );
}
