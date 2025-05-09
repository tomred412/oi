/*
ID: dermotl1
LANG: C++
PROG: rockers
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int n, t, m;
int songs[21];
int best = 0;
int result[21][21][21];  // max songs at tracker with disk disks, with time_left
                         // minutes left on that disk

int solve(int tracker, int disk, int time_left);

int solve_second(int tracker, int disk, int time_left) {
  if (tracker == n || disk == m) {
    return 0;
  }

  int skipped = solve(tracker + 1, disk, time_left);  // skip the song

  int not_skipped = 0;
  if (songs[tracker] <= time_left) {
    not_skipped = solve(tracker + 1, disk, time_left - songs[tracker]) +
                  1;  // do the current
                      // song
  } else if (disk + 1 < m && songs[tracker] <= t) {
    not_skipped = solve(tracker + 1, disk + 1, t - songs[tracker]) +
                  1;  // try other disks
  }
  return max(skipped, not_skipped);
}

int solve(int tracker, int disk, int time_left) {
  if (result[tracker][disk][time_left] == -1) {
    result[tracker][disk][time_left] = solve_second(tracker, disk, time_left);
  }
  return result[tracker][disk][time_left];
}

int main() {
  ifstream fin("rockers.in");
  ofstream fout("rockers.out");

  fin >> n >> t >> m;

  for (int i = 0; i < n; i++) {
    fin >> songs[i];
  }

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      for (int r = 0; r <= t; ++r) {
        result[i][j][r] = -1;
      }
    }
  }

  fout << solve(0, 0, t) << "\n";

  return 0;
}