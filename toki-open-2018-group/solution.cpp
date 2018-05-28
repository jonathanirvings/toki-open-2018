#include "group.h"

#include <vector>
#include <cmath>
#include <iostream>
#include <utility>
using namespace std;

inline double sind(double d) {
	return sin(d * M_PI / 180.0);
}

inline double cosd(double d) {
	return cos(d * M_PI / 180.0);
}

pair<double,double> rotate(double x, double y, double deg){
	double rx = x * cosd(deg) - y * sind(deg);
	double ry = x * sind(deg) + y * cosd(deg);
	return make_pair(rx, ry);
}

int dist(int x, int y, double tx, double ty){
  return round(abs(x - tx) + abs(y - ty));
}

int coba(double x1, double y1, double x2, double y2,int N, vector<int> X, vector<int> Y ){
	int ans = 0;
	pair<double, double> ori1 = rotate(x1, y1, 315);
	pair<double, double> ori2 = rotate(x2, y2, 315);

	for (int i = 0; i < N; i++) {
		ans = max(ans, min(dist(X[i], Y[i], ori1.first, ori1.second) ,
					   	   dist(X[i], Y[i], ori2.first, ori2.second)));
	}

	return ans;
}

int getMinimumDelay(int N, vector<int> X, vector<int> Y) {
  double minX, minY, maxX, maxY;

  minX = 9999999999.9;
  minY = 9999999999.9;
  maxY = -9999999999.9;
  maxX = -9999999999.9;;

  for (int i = 0; i < N; i++) {
  	pair<double,double> rp = rotate(X[i], Y[i], 45.0);
    double x = rp.first;
    double y = rp.second;

    minX = min(minX, x);
    maxX = max(maxX, x);
    minY = min(minY, y);
    maxY = max(maxY, y);
  }

  return min(coba(maxX, minY, minX, maxY, N, X, Y), coba(minX, minY, maxX, maxY, N, X, Y));
}
