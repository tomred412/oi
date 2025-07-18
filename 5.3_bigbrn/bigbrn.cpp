/*
ID: dermotl1
LANG: C++
PROG: bigbrn
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool grid[1001][1001];
int largest_square_here[1001][1001];

int Solve(int x, int y) {
  if (x == 0 || y == 0) return 0;
  if (grid[x][y]) {
    largest_square_here[x][y] = 0;
    return 0;
  }
  if (largest_square_here[x][y] != -1) return largest_square_here[x][y];

  int temp = min(Solve(x, y - 1), Solve(x - 1, y - 1));
  largest_square_here[x][y] = 1 + min(temp, Solve(x - 1, y));

  return largest_square_here[x][y];
}

int main() {
  ifstream fin("bigbrn.in");
  ofstream fout("bigbrn.out");

  int n, t;
  fin >> n >> t;

  for (int i = 0; i < t; ++i) {
    int x, y;
    fin >> x >> y;
    grid[x][y] = true;
  }

  memset(largest_square_here, -1, sizeof(largest_square_here));

  int largest = 0;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      largest = max(largest, Solve(i, j));
    }
  }

  fout << largest << "\n";

  return 0;
}
