/*
ID: dermotl1
LANG: C++
PROG: latin
*/

#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int n;
int square[7][7];
bool used_in_row[7][8];
bool used_in_column[7][8];
long long counts;

int permutations_2[7];
bool visited[7];
long long storage[8];

int locateGroup() {
  for (int i = 0; i < n; ++i) {
    visited[i] = false;
  }
  int best = 1;
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      int length = 0;
      int pos = i;
      do {
        visited[pos] = true;
        pos = permutations_2[pos];
        ++length;
      } while (!visited[pos]);
      if (length > best) best = length;
    }
  }
  return best;
}

long long factorial(int x) {
  long long answer = 1;
  for (int i = x; i >= 2; --i) {
    answer *= i;
  }
  return answer;
}

void dfs(int r, int c) {
  if (r == n) {
    ++counts;
    return;
  }

  if (c == n) {
    if (r == 1) {
      int g = locateGroup();
      if (storage[g] > 0) {
        counts += storage[g];
        return;
      } else {
        long long before = counts;
        dfs(r + 1, 1);
        storage[g] = counts - before;
        return;
      }
    } else {
      dfs(r + 1, 1);
      return;
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (!used_in_row[r][i] && !used_in_column[c][i]) {
      square[r][c] = i;
      used_in_row[r][i] = true;
      used_in_column[c][i] = true;

      if (r == 1) {
        permutations_2[c] = i - 1;
      }

      dfs(r, c + 1);

      used_in_row[r][i] = false;
      used_in_column[c][i] = false;
    }
  }
}

int main() {
  ifstream fin("latin.in");
  ofstream fout("latin.out");
  fin >> n;
  for (int i = 0; i < n; ++i) {
    square[0][i] = i + 1;
    used_in_row[0][i + 1] = true;
    used_in_column[i][i + 1] = true;
  }

  for (int i = 1; i < n; ++i) {
    square[i][0] = i + 1;
    used_in_row[i][i + 1] = true;
    used_in_column[0][i + 1] = true;
  }

  permutations_2[0] = square[1][0] - 1;

  dfs(1, 1);

  long long returned = counts * factorial(n - 1);
  fout << returned << "\n";

  return 0;
}