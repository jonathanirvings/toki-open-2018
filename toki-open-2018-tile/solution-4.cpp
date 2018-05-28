#include "tile.h"

#include <vector>
#include <algorithm>

using namespace std;

vector<int> a;

void init(int N, int K, int Q, int M, std::vector<int> A) {
    a = A;
}

int getNumberOfSpecialTiles(int L, int R) {
  return upper_bound(a.begin(), a.end(), R)
       - lower_bound(a.begin(), a.end(), L);
}
