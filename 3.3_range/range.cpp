/*
ID: dermotl1
LANG: C++
PROG: range
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int field[250][250];
int solve[250][250];
int count_squares[251];  // count the # of squares per each

int main() {
  ifstream fin("range.in");
  ofstream fout("range.out");
  int n;
  fin >> n;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char x;
      fin >> x;
      if (x == '1')
        field[i][j] = 1;
      else
        field[i][j] = 0;
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (field[i][j] == 1) {
        if (i == 0 || j == 0) {
          solve[i][j] = 1;
        } else {
          int minv = solve[i - 1][j];
          if (solve[i][j - 1] < minv) {
            minv = solve[i][j - 1];
          }
          if (solve[i - 1][j - 1] < minv) {
            minv = solve[i - 1][j - 1];
          }
          solve[i][j] = minv + 1;
        }
        for (int k = 2; k <= solve[i][j]; ++k) {
          count_squares[k]++;
        }
      }
    }
  }
  for (int k = 2; k <= n; ++k) {
    if (count_squares[k] > 0) {
      fout << k << " " << count_squares[k] << "\n";
    }
  }
  return 0;
}
