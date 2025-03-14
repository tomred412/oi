/*
ID: dermotl1
LANG: C++
PROG: nocows
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int arra[200][100];

int main() {
  ifstream fin("nocows.in");
  ofstream fout("nocows.out");

  int n, k;
  fin >> n >> k;
  for (int i = 1; i <= k; i++) {
    arra[1][i] = 1;
  }

  for (int i = 2; i <= n; i++) {
    for (int j = 2; j <= k; j++) {
      for (int l = 1; l <= i - 2; l++) {  // # nodes in left section
        int r = i - l - 1;
        arra[i][j] = (arra[i][j] + arra[l][j - 1] * arra[r][j - 1]) % 9901;
      }
    }
  }
  fout << (arra[n][k] - arra[n][k - 1] + 9901) % 9901 << "\n";
}
