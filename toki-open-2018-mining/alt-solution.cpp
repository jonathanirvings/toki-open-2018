#include "mining.h"
#include <vector>
#include <set>
#include <cmath>
#include <iostream>
#include <algorithm> 
#include <cstring>
using namespace std;

bool ok(int x, int y, int a, int b) {
  int d = (x - a) * (x - a) + (y - b) * (y - b);
  int w = (int) round(sqrt(d));
  return (w * w == d);
}

bool isPossible(int x, int y, set<pair<int,int>>& pot) {
  if (pot.size() == 0)
    return true;
  int N = pot.size();
  for (auto p: pot) {
    if (!ok(p.first, p.second, x, y)) N--;
  }
  if (N) return true;
  return false;
}

void init_potential(vector<int>& solX, vector<int>& solY, vector<pair<int,int>>& no, set<pair<int,int>>& potential) {
  for (int i: solX)
    for (int j: solY){ 
      bool fail = false;
      for (int k=0;k<solX.size();k++){
        int tx = solX[k];
        int ty = solY[k];
        if (fail) break;  
        if (!ok(i,j,tx,ty)) {
          fail = true;
        }
      }
      for (auto n: no) {
        int tx = n.first;
        int ty = n.second;
        if (fail) break;  
        if (ok(i,j,tx,ty)) {
          fail = true;
        }
      }
      if (!fail) {
        potential.insert(make_pair(i,j));
      }
    }
}

vector<pair<int,int>> p_triplet;

void gen_triplet() {
  for (int i=-1000;i<=1000;i++)
    for (int j=-1000;j<=1000;j++){
      if (i == 0 || j == 0) continue;
      if (ok(1000 + i,1000 + j,1000, 1000))
        p_triplet.push_back(make_pair(i,j));
    }
  cerr<<p_triplet.size()<<endl;
}

void findGold() {
  // one time only
  if (p_triplet.size() == 0)
    gen_triplet();

  int i = 1;
  vector<int> solX, solY;
  vector<pair<int,int>> no;
  set<pair<int,int>> pot;
  vector<pair<int,int>> ask_order;

  int yes = 0;
  for (int i=1;i<=1000;i++) {
    ask_order.push_back(make_pair(i,i));
  }

  for (int i=0;i<1000;i++) {
    int x = ask_order[i].first;
    int y = ask_order[i].second;
    // 10000 1000 heuristic
    if (i == 999 && yes == 0) {
      answer(1000,1000);
      return;
    }
    // diagonal solution heuristic
    if (i == 999 && yes == 1) {
      break;
    }

    if (yes < 29 && isPossible(x,y, pot) && isIntegerDistance(x, y)) {
      solX.push_back(x);
      solY.push_back(y);
      yes++;
      if (yes == 1) {
        for (int j=1;j<=1000;j++) { pot.insert(make_pair(x, j)); pot.insert(make_pair(j, y));}
        for (auto p: p_triplet) {
          int x2 = x + p.first;
          int y2 = y + p.second;
          if (x2 >= 1 && x2 <= 1000 && y2 >= 1 && y2 <= 1000)
            pot.insert(make_pair(x2, y2));
        }
        //flip heuristic
        reverse(ask_order.begin() + i + 1, ask_order.end());
      } else {
        set<pair<int,int>> rm_list;
        for (auto p: pot) {
          if (!ok(p.first, p.second, x, y))
            rm_list.insert(p);
        }
        for (auto rm: rm_list){
          pot.erase(rm);
        }
      }
    } else {
      no.push_back(make_pair(x, y));
    }
  }

  set<pair<int,int>> potential;
  init_potential(solX, solY, no, potential);

  // double cross validation (wat)
  while (potential.size() > 2) {
    int tx = (*potential.begin()).first;
    int ty = -1;
    for (auto tmp: potential) {
      if (tmp.second != tx && tmp.first != tx) {
        ty = tmp.second;
        break;
      }
    }
    bool ok = isIntegerDistance(tx, ty);

    set<pair<int,int>> rm_list;
    for (auto P: potential) {
      if (ok && P.first != tx && P.second != ty)
        rm_list.insert(P);
      if (!ok && (P.first == tx || P.second == ty))
        rm_list.insert(P);
    }
    for (auto rm: rm_list){
      potential.erase(rm);
    }
  }
  
  if (potential.size() == 1 || 
      isIntegerDistance((*potential.begin()).first,(*potential.begin()).second))
    answer((*potential.begin()).first,(*potential.begin()).second);
  else
    answer((*potential.rbegin()).first,(*potential.rbegin()).second);
  return;
}
