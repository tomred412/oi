/*
ID: dermotl1
LANG: C++
PROG: game1
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int original[100];

int sums(int start, int end) {
  int total = 0;
  for (int i = start; i < end; ++i) {
    total += original[i];
  }
  return total;
}

int result[100][101];

int remainders(int, int);

int remainders_implement(int start,
                         int length) {  // pick left or right when given start
                                        // and length?, right = true
  if (length == 2) {
    if (original[start] > original[start + 1])
      return original[start + 1];
    else
      return original[start];
  }

  int left_score = original[start] + remainders(start + 1, length - 1);

  int right_score =
      original[start + length - 1] + remainders(start, length - 1);

  if (left_score > right_score) {
    return sums(start, start + length) - left_score;
  } else {
    return sums(start, start + length) - right_score;
  }
}

int remainders(int start, int length) {
  if (result[start][length] == 0) {
    result[start][length] = remainders_implement(start, length);
  }
  return result[start][length];
}

int main() {
  ifstream fin("game1.in");
  ofstream fout("game1.out");

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> original[i];
  }

  fout << sums(0, n) - remainders(0, n) << " " << remainders(0, n) << "\n";
  return 0;
}
