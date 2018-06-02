#include "mining.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <vector>

static int X, Y;
static const int M = 1000;
static const int N = 1000;

static int basic_number_of_queries = 0;
static const int DIFF = 1884187401; // The value of our hex password % INT_MAX.
static const int INITIAL_VALUE = 20180526; // The first day of TOKI Open 2018.
static long long number_of_queries_times_diff = INITIAL_VALUE;
static const char SYMBOL = '*';
static std::vector<char> vector_number_of_queries;

static void wrongAnswer() {
  puts("WA");
  exit(0);
}

static void increaseCounter() {
  ++basic_number_of_queries;
  number_of_queries_times_diff += DIFF;
  vector_number_of_queries.push_back(SYMBOL);
  printf(".");
}

static void checkCounter() {
  if (basic_number_of_queries < 0) {
    wrongAnswer();
  }
  if ((long long)basic_number_of_queries * DIFF + INITIAL_VALUE
      != number_of_queries_times_diff) {
    wrongAnswer();
  }
  if (vector_number_of_queries.size() != basic_number_of_queries) {
    wrongAnswer();
  }
  puts("");
}

static bool isPerfectSquare(int K) {
  static const int square_check_offset = 3;
  int sqrt_K = (int)round(sqrt(K));
  for (int i = sqrt_K - square_check_offset;
       i <= sqrt_K + square_check_offset; ++i) {
    if (i * i == K) {
      return true;
    }
  }
  return false;
}

bool isIntegerDistance(int A, int B) {
  if (A < 1 || A > M) {
    printf("WA: The first coordinate is not between 1 and %d\n", M);
    exit(0);
  }
  if (B < 1 || B > N) {
    printf("WA: The second coordinate is not between 1 and %d\n", N);
    exit(0);
  }
  increaseCounter();
  return isPerfectSquare((A - X) * (A - X) + (B - Y) * (B - Y));
}

void answer(int A, int B) {
  if (A != X || B != Y) {
    printf("WA: You guessed the wrong coordinate\n");
    exit(0);
  }
  checkCounter();
  printf("%d\n", basic_number_of_queries);
  puts("df838ed4a0d56d7c080adbc162061887f7513f2f44d8892df50f99961f634ece");
  exit(0);
}

int main() {
  if (scanf("%d %d", &X, &Y) != 2) {
    wrongAnswer();
  }

  if (!(std::cin >> std::ws).eof()) {
    wrongAnswer();
  }
  findGold();

  printf("WA: findGold() must call answer(A, B) method\n");
  return 0;
}
