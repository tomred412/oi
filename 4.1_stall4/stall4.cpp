/*
ID: dermotl1
LANG: C++
PROG: stall4
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int cow_likes[201][201];
int cow_likes_count[201];
int final_match[201];
bool visited[201];
int n, m;
int result;

bool solve(int cow) {
  for (int i = 0; i < cow_likes_count[cow]; ++i) {
    int stall = cow_likes[cow][i];

    if (visited[stall] == false) {
      visited[stall] = true;
      if (final_match[stall] == 0 ||
          solve(final_match[stall])) {  // if stall isn't taken/other cow can be
                                        // reshuffled
        final_match[stall] = cow;
        return true;
      }
    }
  }
  return false;
}

int main() {
  ifstream fin("stall4.in");
  ofstream fout("stall4.out");

  fin >> n >> m;

  for (int i = 1; i <= n; ++i) {
    fin >> cow_likes_count[i];
    for (int j = 0; j < cow_likes_count[i]; ++j) {
      fin >> cow_likes[i][j];
    }
  }

  for (int i = 1; i <= n; ++i) {
    memset(visited, false, sizeof(visited));
    if (solve(i)) result++;
  }

  fout << result << "\n";

  return 0;
}