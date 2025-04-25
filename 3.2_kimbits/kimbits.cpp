/*
ID: dermotl1
LANG: C++
PROG: kimbits
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int64_t cont;

int64_t cxy[31][31];

void choose() {
  cxy[0][0] = 0;
  cxy[1][0] = 1;
  cxy[1][1] = 1;
  for (int64_t i = 0; i < 31; ++i) {
    cxy[i][0] = 1;
    cxy[i][i] = 1;
    for (int64_t j = 1; j <= i - 1; ++j) {
      cxy[i][j] = cxy[i - 1][j - 1] + cxy[i - 1][j];
    }
  }
}

int64_t one_or_zero(int64_t n, int64_t l, int64_t i) {
  cont = 0;
  while (l >= 0) {
    cont = cont + cxy[n - 1][l];
    l--;
  }
  if (cont < i) return 1;
  return 0;
}

int main() {
  ifstream fin("kimbits.in");
  ofstream fout("kimbits.out");

  choose();

  int64_t n, l, i;
  fin >> n >> l >> i;
  int64_t n_1 = n;

  for (int64_t j = 0; j < n_1; ++j) {
    int64_t a = one_or_zero(n, l, i);
    fout << a;
    if (a == 0) {
      n = n - 1;
    } else {
      n = n - 1;
      l = l - 1;
      i = i - cont;
    }
  }
  fout << "\n";

  return 0;
}
