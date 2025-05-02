/*
ID: dermotl1
LANG: C++
PROG: fence
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int adj[501][1024];
int amount[501];        // stores amount of neighbors per
int visited[501][501];  // how many times visited
int counts[501][501];
int path[1025];
int path_position = 0;

void insert(int x, int y) {  // add x into y adj (sorted)
  int i;
  for (i = amount[x]; i > 0 && adj[x][i - 1] > y; --i) {
    adj[x][i] = adj[x][i - 1];
  }
  adj[x][i] = y;
  amount[x]++;
  counts[x][y]++;
}

void solve(int x) {
  for (int i = 0; i < amount[x]; ++i) {
    int y = adj[x][i];
    if (visited[x][y] < counts[x][y]) {
      visited[x][y]++;
      visited[y][x]++;
      solve(y);
    }
  }
  path[path_position++] = x;
}

int main() {
  ifstream fin("fence.in");
  ofstream fout("fence.out");

  int f;
  fin >> f;
  int x, y;

  for (int i = 0; i < f; ++i) {
    fin >> x >> y;
    insert(x, y);
    insert(y, x);
  }

  int start = -1;
  for (int i = 1; i < 501; ++i) {
    if (amount[i] % 2 == 1) {
      if (start == -1 || i < start) start = i;  // pick odd
    }
  }
  if (start == -1) {
    for (int i = 1; i < 501; ++i) {
      if (amount[i] != 0) {
        start = i;
        break;
      }
    }
  }

  solve(start);

  for (int i = path_position - 1; i >= 0; --i) {
    fout << path[i] << "\n";
  }
  return 0;
}
