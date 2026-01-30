/*
ID: dermotl1
LANG: C++
PROG: betsy
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
int answer;
bool visited[8][8];
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, -1, 0, 1};

int countNeighbors(int x, int y) {
  int count = 0;
  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[ny][nx]) {
      ++count;
    }
  }
  return count;
}

void solve(int x, int y, int visited_count) {
  if (x == 0 && y == n - 1) {
    if (visited_count == n * n) {
      ++answer;
    }
    return;
  }

  int must_visit_x = -1, must_visit_y = -1;
  int dead_ends = 0;

  for (int i = 0; i < 4; ++i) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[ny][nx]) {
      if (nx == 0 && ny == n - 1) {
        continue;
      }
      if (countNeighbors(nx, ny) < 2) {
        ++dead_ends;
        must_visit_x = nx;
        must_visit_y = ny;
      }
    }
  }

  if (dead_ends > 1) return;

  if (dead_ends == 1) {
    visited[must_visit_y][must_visit_x] = true;
    solve(must_visit_x, must_visit_y, visited_count + 1);
    visited[must_visit_y][must_visit_x] = false;
    return;
  }

  for (int i = 0; i < 4; ++i) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[ny][nx]) {
      if (nx == 0 && ny == n - 1 && visited_count + 1 != n * n) continue;
      visited[ny][nx] = true;
      solve(nx, ny, visited_count + 1);
      visited[ny][nx] = false;
    }
  }
}

int main() {
  ifstream fin("betsy.in");
  ofstream fout("betsy.out");

  fin >> n;

  visited[0][0] = true;
  solve(0, 0, 1);

  fout << answer << "\n";

  return 0;
}
