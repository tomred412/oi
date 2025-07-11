/*
ID: dermotl1
LANG: C++
PROG: schlnet
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

bool reachable[102][102];
bool done = false;
int n;
int answer_a = 102;
int current_subset[102];
int length = 0;

bool visited[102];
/*
int exponent_2(int x) {
  int result = 1;
  for (int i = 0; i < x; ++i) {
    result = result * 2;
  }
  return result;
}

void TryAll(int start, int size) {
  if (done) return;
  if (length == size) {
    bool received_software[102];
    memset(received_software, false, 102);

    for (int i = 0; i < length; ++i) {
      int x = current_subset[i];

      for (int j = 1; j <= n; ++j) {
        if (reachable[x][j]) received_software[j] = true;
      }
    }

    bool all_received = true;
    for (int i = 1; i <= n; ++i) {
      if (!received_software[i]) {
        all_received = false;
        break;
      }
    }

    if (all_received) {
      answer_a = size;
      done = true;
    }
    return;
  }

  for (int i = start; i <= n; ++i) {
    current_subset[length++] = i;
    TryAll(i + 1, size);
    length--;
  }
}
*/
int main() {
  ifstream fin("schlnet.in");
  ofstream fout("schlnet.out");

  fin >> n;
  for (int i = 1; i <= n; ++i) {
    reachable[i][i] = true;
    int j;

    while (true) {
      fin >> j;
      if (j == 0) break;
      reachable[i][j] = true;
    }
  }

  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (reachable[i][k] && reachable[k][j]) {
          reachable[i][j] = true;
        }
      }
    }
  }
  /*
    int subtask_a = n;
    int total_subsets = 1;
    for (int i = 0; i < n; ++i) {
      total_subsets = total_subsets * 2;
    }

    for (int i = 1; i <= n && !done; ++i) {  // try all subsets of size i
      length = 0;
      TryAll(1, i);
    }
  */
  int no_path_to = 0;
  int no_path_from = 0;
  int number_of_linked_togethers = 0;

  for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
      number_of_linked_togethers++;

      bool no_path_into_here = true;
      bool no_path_from_here = true;

      for (int j = 1; j <= n; ++j) {
        if (reachable[i][j] && !reachable[j][i])
          no_path_from_here = false;  // path into i exists, but one out doesnt
        if (reachable[j][i] && !reachable[i][j])
          no_path_into_here = false;  // path from i exists, but one in doesnt
      }
      if (no_path_into_here) no_path_to++;
      if (no_path_from_here) no_path_from++;

      for (int j = 1; j <= n; ++j) {
        if (reachable[i][j] && reachable[j][i]) {
          visited[j] = true;
        }
      }
    }
  }
  int answer_b = 0;
  if (number_of_linked_togethers != 1) answer_b = max(no_path_to, no_path_from);

  fout << no_path_to << "\n" << answer_b << "\n";

  return 0;
}
