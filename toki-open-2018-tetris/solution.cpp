#include "tetris.h"
#include <bits/stdc++.h>

using namespace std;

int n;
string s;
vector<int> answer;
int mem[207][207][5][2];

// Stat:
//
// __  #_  _#  #_  _#
// __  #_  _#  _#  #_
// 0   1   2   3   4


// ============================================================================
// DP to Check Validity
// ============================================================================

bool DP(int left, int right, int stat, bool must_finish) {
	if (left == right) return (stat == 0);
	if (stat == 0 && must_finish) return (left == right);
	if (mem[left][right][stat][must_finish] != -1) return mem[left][right][stat][must_finish];
	
	bool ret = false;
	
	if (s[left] == 'O') {
		// Pop
		
		// Push
		
		// Update
		ret |= DP(left+1, right, stat, must_finish); // ori: 1
		
		
	} else if (s[left] == 'T') {
		// Pop
		
		// Push
		if (stat == 1 || stat == 3) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 1, true) && DP(mid, right, stat, must_finish)); // ori: 1
			}
		}
		if (stat == 2 || stat == 4) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 2, true) && DP(mid, right, stat, must_finish)); // ori: 3
			}
		}
		
		// Update
		if (stat == 0) {
			ret |= DP(left+1, right, 1, must_finish); // ori: 1
			ret |= DP(left+1, right, 2, must_finish); // ori: 3
		}
		if (stat == 1) {
			ret |= DP(left+1, right, 4, must_finish); // ori: 3
		}
		if (stat == 2) {
			ret |= DP(left+1, right, 3, must_finish); // ori: 1
		}
		if (stat == 3) {
			ret |= DP(left+1, right, 2, must_finish); // ori: 3
		}
		if (stat == 4) {
			ret |= DP(left+1, right, 1, must_finish); // ori: 1
		}
		
	
	} else if (s[left] == 'J') {
		// Pop
		if (stat == 2) {
		    ret |= DP(left+1, right, 0, must_finish); // ori: 1
		}
		
		// Push
		if (stat == 1 || stat == 3) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 1, true) && DP(mid, right, stat, must_finish)); // ori: 1
			}
		}
		if (stat != 0) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 2, true) && DP(mid, right, stat, must_finish)); // ori: 3
			}
		}
		
		// Update
		if (stat == 0) {
			ret |= DP(left+1, right, 1, must_finish); // ori: 1
			ret |= DP(left+1, right, 2, must_finish); // ori: 3
		}
		if (stat == 4) {
		    ret |= DP(left+1, right, 1, must_finish); // ori: 1
		}
		
		
	} else if (s[left] == 'L') {
		// Pop
		if (stat == 1) {
		    ret |= DP(left+1, right, 0, must_finish); // ori: 3
		}
		
		// Push
		if (stat == 2 || stat == 4) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 2, true) && DP(mid, right, stat, must_finish)); // ori: 3
			}
		}
		if (stat != 0) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 1, true) && DP(mid, right, stat, must_finish)); // ori: 1
			}
		}
		
		// Update
		if (stat == 0) {
			ret |= DP(left+1, right, 1, must_finish); // ori: 1
			ret |= DP(left+1, right, 2, must_finish); // ori: 3
		}
		if (stat == 3) {
		    ret |= DP(left+1, right, 2, must_finish); // ori: 3
		}
		
		
	} else if (s[left] == 'S') {
		// Pop
		
		// Push
		if (stat == 2 || stat == 4) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 3, true) && DP(mid, right, stat, must_finish)); // ori: 1
			}
		}
		
		// Update
		if (stat == 0) {
		    ret |= DP(left+1, right, 3, must_finish); // ori: 1
		}
		if (stat == 1) {
		    ret |= DP(left+1, right, 1, must_finish); // ori: 1
		}
		if (stat == 3) {
		    ret |= DP(left+1, right, 3, must_finish); // ori: 1
		}
		
		
	} else if (s[left] == 'Z') {
		// Pop
		
		// Push
		if (stat == 1 || stat == 3) {
			for (int mid = left + 1; mid <= right; mid++) {
				ret |= (DP(left+1, mid, 4, true) && DP(mid, right, stat, must_finish)); // ori: 1
			}
		}
		
		// Update
		if (stat == 0) {
		    ret |= DP(left+1, right, 4, must_finish); // ori: 1
		}
		if (stat == 2) {
		    ret |= DP(left+1, right, 2, must_finish); // ori: 1
		}
		if (stat == 4) {
		    ret |= DP(left+1, right, 4, must_finish); // ori: 1
		}
		
		
	}
	
	return mem[left][right][stat][must_finish] = ret;
}


// ============================================================================
// Recursive to Get the Answer, basically same as previous one
// ============================================================================

void DP2(int left, int right, int stat, bool must_finish) {
	if (left == right) return;
	if (stat == 0 && must_finish) return;
	
	if (s[left] == 'O') {
		// Pop
		
		// Push
		
		// Update
		if (DP(left+1, right, stat, must_finish)) {
		    answer.push_back(1);
		    DP2(left+1, right, stat, must_finish);
		    return;
		}
		
		
	} else if (s[left] == 'T') {
		// Pop
		
		// Push
		if (stat == 1 || stat == 3) {
			for (int mid = left + 1; mid <= right; mid++) {
				if (DP(left+1, mid, 1, true) && DP(mid, right, stat, must_finish)) {
				    answer.push_back(1);
		            DP2(left+1, mid, 1, true);
		            DP2(mid, right, stat, must_finish);
		            return;
				}
			}
		}
		if (stat == 2 || stat == 4) {
			for (int mid = left + 1; mid <= right; mid++) {
				if (DP(left+1, mid, 2, true) && DP(mid, right, stat, must_finish)) {
				    answer.push_back(3);
		            DP2(left+1, mid, 2, true);
		            DP2(mid, right, stat, must_finish);
		            return;
				}
			}
		}
		
		// Update
		if (stat == 0) {
			if (DP(left+1, right, 1, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 1, must_finish);
	            return;
			}
			if (DP(left+1, right, 2, must_finish)) {
			    answer.push_back(3);
	            DP2(left+1, right, 2, must_finish);
	            return;
			}
		}
		if (stat == 1) {
			if (DP(left+1, right, 4, must_finish)) {
			    answer.push_back(3);
	            DP2(left+1, right, 4, must_finish);
	            return;
			}
		}
		if (stat == 2) {
		    if (DP(left+1, right, 3, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 3, must_finish);
	            return;
			}
		}
		if (stat == 3) {
			if (DP(left+1, right, 2, must_finish)) {
			    answer.push_back(3);
	            DP2(left+1, right, 2, must_finish);
	            return;
			}
		}
		if (stat == 4) {
			if (DP(left+1, right, 1, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 1, must_finish);
	            return;
			}
		}
		
	
	} else if (s[left] == 'J') {
		// Pop
		if (stat == 2) {
		    if (DP(left+1, right, 0, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 0, must_finish);
	            return;
			}
		}
		
		// Push
		if (stat == 1 || stat == 3) {
			for (int mid = left + 1; mid <= right; mid++) {
			    if (DP(left+1, mid, 1, true) && DP(mid, right, stat, must_finish)) {
			        answer.push_back(1);
			        DP2(left+1, mid, 1, true);
			        DP2(mid, right, stat, must_finish);
	                return;
			    }
			}
		}
		if (stat != 0) {
			for (int mid = left + 1; mid <= right; mid++) {
				if (DP(left+1, mid, 2, true) && DP(mid, right, stat, must_finish)) {
			        answer.push_back(3);
			        DP2(left+1, mid, 2, true);
			        DP2(mid, right, stat, must_finish);
	                return;
			    }
			}
		}
		
		// Update
		if (stat == 0) {
		    if (DP(left+1, right, 1, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 1, must_finish);
	            return;
			}
			if (DP(left+1, right, 2, must_finish)) {
			    answer.push_back(3);
	            DP2(left+1, right, 2, must_finish);
	            return;
			}
		}
		if (stat == 4) {
		    if (DP(left+1, right, 1, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 1, must_finish);
	            return;
			}
		}
		
		
	} else if (s[left] == 'L') {
		// Pop
		if (stat == 1) {
		    if (DP(left+1, right, 0, must_finish)) {
			    answer.push_back(3);
	            DP2(left+1, right, 0, must_finish);
	            return;
			}
		}
		
		// Push
		if (stat == 2 || stat == 4) {
			for (int mid = left + 1; mid <= right; mid++) {
				if (DP(left+1, mid, 2, true) && DP(mid, right, stat, must_finish)) {
			        answer.push_back(3);
			        DP2(left+1, mid, 2, true);
			        DP2(mid, right, stat, must_finish);
	                return;
			    }
			}
		}
		if (stat != 0) {
			for (int mid = left + 1; mid <= right; mid++) {
			    if (DP(left+1, mid, 1, true) && DP(mid, right, stat, must_finish)) {
			        answer.push_back(1);
			        DP2(left+1, mid, 1, true);
			        DP2(mid, right, stat, must_finish);
	                return;
			    }
			}
		}
		
		// Update
		if (stat == 0) {
			if (DP(left+1, right, 1, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 1, must_finish);
	            return;
			}
			if (DP(left+1, right, 2, must_finish)) {
			    answer.push_back(3);
	            DP2(left+1, right, 2, must_finish);
	            return;
			}
		}
		if (stat == 3) {
		    if (DP(left+1, right, 2, must_finish)) {
			    answer.push_back(3);
	            DP2(left+1, right, 2, must_finish);
	            return;
			}
		}
		
		
	} else if (s[left] == 'S') {
		// Pop
		
		// Push
		if (stat == 2 || stat == 4) {
			for (int mid = left + 1; mid <= right; mid++) {
			    if (DP(left+1, mid, 3, true) && DP(mid, right, stat, must_finish)) {
			        answer.push_back(1);
			        DP2(left+1, mid, 3, true);
			        DP2(mid, right, stat, must_finish);
	                return;
			    }
			}
		}
		
		// Update
		if (stat == 0) {
		    if (DP(left+1, right, 3, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 3, must_finish);
	            return;
			}
		}
		if (stat == 1) {
		    if (DP(left+1, right, 1, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 1, must_finish);
	            return;
			}
		}
		if (stat == 3) {
		    if (DP(left+1, right, 3, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 3, must_finish);
	            return;
			}
		}
		
		
	} else if (s[left] == 'Z') {
		// Pop
		
		// Push
		if (stat == 1 || stat == 3) {
			for (int mid = left + 1; mid <= right; mid++) {
			    if (DP(left+1, mid, 4, true) && DP(mid, right, stat, must_finish)) {
			        answer.push_back(1);
			        DP2(left+1, mid, 4, true);
			        DP2(mid, right, stat, must_finish);
	                return;
			    }
			}
		}
		
		// Update
		if (stat == 0) {
		    if (DP(left+1, right, 4, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 4, must_finish);
	            return;
			}
		}
		if (stat == 2) {
		    if (DP(left+1, right, 2, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 2, must_finish);
	            return;
			}
		}
		if (stat == 4) {
		    if (DP(left+1, right, 4, must_finish)) {
			    answer.push_back(1);
	            DP2(left+1, right, 4, must_finish);
	            return;
			}
		}
		
		
	}
	
	return;
}


// ============================================================================
// Main Program
// ============================================================================

vector<int> arrangeTetrominoes(int N, string S, int Q) {
	n = N;
	s = S;
	
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k < 5; k++) {
				mem[i][j][k][0] = -1;
				mem[i][j][k][1] = -1;
			}
		}
	}
	
	if (DP(0, n, 0, false)) {
		DP2(0, n, 0, false);
	}
	
	return answer;
}
