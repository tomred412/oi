/*
ID: dermotl1
LANG: C++
PROG: concom
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int own[101][101];  // in %
bool control[101][101];

void find(int n) {
  for (int i = 0; i < 100; i++) {
    control[i][i] = true;
  }
  for (int i = 1; i <= 100; i++) {
    for (int j = 1; j <= 100; j++) {
      if (own[i][j] > 50) control[i][j] = true;
    }
  }

  bool yes = true;
  while (yes) {
    yes = false;
    for (int i = 1; i <= 100; i++) {
      for (int j = 1; j <= 100; j++) {
        if (control[i][j] || i == j) continue;
        int total = 0;
        for (int k = 1; k <= 100; k++) {
          if (control[i][k]) total += own[k][j];
        }
        if (total > 50) {
          control[i][j] = true;
          yes = true;
        }
      }
    }
  }
}

int main() {
  ifstream fin("concom.in");
  ofstream fout("concom.out");

  int n;
  fin >> n;

  for (int i = 0; i < n; i++) {
    int a, b, c;
    fin >> a >> b >> c;
    own[a][b] += c;
  }
  find(n);
  for (int i = 1; i <= 100; i++) {
    for (int j = 1; j <= 100; j++) {
      if (i != j && control[i][j]) {
        fout << i << " " << j << "\n";
      }
    }
  }
}
