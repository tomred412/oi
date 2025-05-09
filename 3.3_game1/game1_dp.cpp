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
int sum[101];
int result[100][101];

void sums(int n) {
  int total = 0;
  for (int i = 0; i < n; ++i) {
    sum[i + 1] += sum[i] + original[i];
  }
}

int main() {
  ifstream fin("game1.in");
  ofstream fout("game1.out");

  int n;
  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> original[i];
  }

  sums(n);

  for (int i = 0; i < n; ++i) {
    result[i][i] = original[i];
  }

  for (int i = 2; i <= n; ++i) {
    for (int j = 0; j + i - 1 < n; ++j) {
      int r = j + i - 1;
      int total = sum[r + 1] - sum[j];
      result[j][r] = total - min(result[j + 1][r], result[j][r - 1]);
    }
  }

  fout << result[0][n - 1] << " " << sum[n] - result[0][n - 1] << "\n";
  return 0;
}
