#include "table.h"
#include <bits/stdc++.h>

using namespace std;

long long i, j, k, l, MOD;
long long a[107], cyc[107], tmp1[107], tmp2[107];
long long mem1[107][107], mem2[67][107][107], mem3[107][107];
bool isFirst;

long long power(long long x, long long y) {
    if (y == 0) return 1;
    if (y == 1) return x % 100;
    if (y % 2 == 1) return x * power(x, y-1) % 100;
    long long tmp = power(x, y/2);
    return tmp * tmp % 100;
}

long long DP2(long long bit, long long to, long long from) {
    if (bit == 0) {
        if (from == 0 && to == 0) return 2;
        if (to == 0) return 1;
        if (to == from) return 1;
        return 0;
    }
    if (mem2[bit][to][from] != -1) return mem2[bit][to][from];
    
    long long ans = 0;
    for (int i = 0; i < 100; i++) {
        ans = (ans + DP2(bit-1, i, from) * DP2(bit-1, (to-i+100) % 100, from)) % MOD;
    }
    
    return mem2[bit][to][from] = ans;
}

long long DP1(long long pos, long long sum) {
    if (pos == 100) {
        if (sum == 13) return 1;
        return 0;
    }
    if (mem1[pos][sum] != -1) return mem1[pos][sum];
    
    long long ans = 0;
    for (int i = 0; i < 100; i++) {
        ans = (ans + mem3[pos][i] * DP1(pos+1, (sum+i) % 100)) % MOD;
    }
    
    return mem1[pos][sum] = ans;
}

int countSubsets(int M, int N, int K, vector<int> C, vector<int> D) {
	MOD = 1000000007;
    
    for (i = 0; i < K; i++) {
        a[power(C[i], D[i])]--;
    }
    
    for (i = 0; i < 100; i++) {
        long long many = (M + 100 - i) / 100;
        if (i == 0) many = M / 100;
        for (j = 0; j < 100; j++) cyc[j] = -1;
        
        long long x = i;
        long long excess = N;
        long long num = 0;
        while (excess > 0) {
        	if (cyc[x] != -1) break;
            cyc[x] = num++;
            a[x] += many;
            x = (x * i) % 100;
            excess--;
        }
        
        if (excess > 0) {
            long long mul = excess / (num - cyc[x]);
            excess -= mul * (num - cyc[x]);
            
            for (j = 0; j < 100; j++) if (cyc[j] >= cyc[x]) {
                a[j] += many * mul;
            }
            
            while (excess > 0) {
                a[x] += many;
                x = (x * i) % 100;
                excess--;
            } 
        }
    }
    
    for (i = 0; i <= 100; i++) {
        for (j = 0; j <= 100; j++) {
            for (k = 0; k <= 60; k++) {
                mem2[k][i][j] = -1;
            }
            mem1[i][j] = -1;
            mem3[i][j] = -1;
        }
    }
    
    for (i = 0; i < 100; i++) {
        isFirst = true;
        for (j = 0; j < 100; j++) tmp1[j] = 0;
        tmp1[0] = 1;
        
        for (j = 0; j < 60; j++) {
            if (((1LL << j) & a[i]) > 0) {
                if (isFirst) {
                    isFirst = false;
                    for (k = 0; k < 100; k++) tmp1[k] = DP2(j,k,i);
                } else {
                    for (k = 0; k < 100; k++) tmp2[k] = 0;                   
                    for (k = 0; k < 100; k++) {
                        for (l = 0; l < 100; l++) {
                            tmp2[(k+l) % 100] = (tmp2[(k+l) % 100] + tmp1[k] * DP2(j,l,i)) % MOD;
                        }   
                    }
                    for (k = 0; k < 100; k++) tmp1[k] = tmp2[k];
                }
            }
        }
        for (j = 0; j < 100; j++) mem3[i][j] = tmp1[j];
    }
    
    return DP1(0,0);
}
