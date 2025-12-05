/*
ID: dermotl1
LANG: C++
PROG: wissqu
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

char grid[4][4];
bool used[4][4];

int remaining[5] = {3, 3, 3, 4, 3};
struct moves {
  char cow;
  int x, y;
};
moves answer[16];
moves current[16];
long long total;
bool printed_answer;

int x_direction[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
int y_direction[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

bool inside(int x, int y) { return x >= 0 && x < 4 && y >= 0 && y < 4; }

bool canPlace(int herd, int x, int y) {
  if (used[x][y]) return false;
  if (remaining[herd] == 0) return false;
  char temp = 'A' + herd;
  for (int i = 0; i < 9; ++i) {
    int new_x = x + x_direction[i];
    int new_y = y + y_direction[i];
    if (inside(new_x, new_y) && grid[new_x][new_y] == temp) return false;
  }
  return true;
}

void dfs(int depth) {
  if (depth == 16) {
    ++total;
    if (!printed_answer) {
      for (int i = 0; i < 16; ++i) {
        answer[i] = current[i];
      }
      printed_answer = true;
    }
    return;
  }
  for (int i = 0; i < 5; ++i) {
    if (depth == 0 && i != 3) continue;
    if (remaining[i] == 0) continue;
    char temp = 'A' + i;

    for (int x = 0; x < 4; ++x) {
      for (int y = 0; y < 4; ++y) {
        if (canPlace(i, x, y)) {
          char old = grid[x][y];
          grid[x][y] = temp;
          used[x][y] = true;
          --remaining[i];

          current[depth].cow = temp;
          current[depth].x = x;
          current[depth].y = y;

          dfs(depth + 1);

          ++remaining[i];
          used[x][y] = false;
          grid[x][y] = old;
        }
      }
    }
  }
}

int main() {
  ifstream fin("wissqu.in");
  ofstream fout("wissqu.out");

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      fin >> grid[i][j];
    }
  }

  dfs(0);

  for (int i = 0; i < 16; ++i) {
    fout << answer[i].cow << " " << (answer[i].x + 1) << " "
         << (answer[i].y + 1) << "\n";
  }

  fout << total << "\n";

  return 0;
}