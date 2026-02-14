/*
ID: dermotl1
LANG: C++
PROG: clocks
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

int original_clocks[9];  // 0 based (A = 0, etc.)
int current_clocks[9];
int press_count[10];

int moves[10][6] = {
    {0},           {0, 1, 3, 4, -1},    {0, 1, 2, -1}, {1, 2, 4, 5, -1},
    {0, 3, 6, -1}, {1, 3, 4, 5, 7, -1}, {2, 5, 8, -1}, {3, 4, 6, 7, -1},
    {6, 7, 8, -1}, {4, 5, 7, 8, -1}};  // 1 based moves

int min_total_moves = numeric_limits<int>::max();
int best[10];

void checkCombination() {
  for (int i = 0; i < 9; ++i) {
    current_clocks[i] = original_clocks[i];
  }

  for (int i = 1; i <= 9; ++i) {
    int times = press_count[i];

    if (times > 0) {
      for (int j = 0; j < 6; ++j) {
        int pos = moves[i][j];

        if (pos == -1) break;
        current_clocks[pos] += times;
      }
    }
  }

  for (int i = 0; i < 9; ++i) {
    if (current_clocks[i] % 4 != 0) return;
  }

  int total_moves = 0;

  for (int i = 1; i <= 9; ++i) {
    total_moves += press_count[i];
  }

  if (total_moves <
      min_total_moves) {  // don't update for = (lexiographically already)
    min_total_moves = total_moves;

    for (int i = 1; i <= 9; ++i) {
      best[i] = press_count[i];
    }
  }
}

int main() {
  ifstream fin("clocks.in");
  ofstream fout("clocks.out");

  for (int i = 0; i < 9; ++i) {
    int temp;
    fin >> temp;
    if (temp == 12)
      original_clocks[i] = 0;
    else
      original_clocks[i] = temp / 3;
  }

  for (press_count[1] = 0; press_count[1] <= 3; ++press_count[1]) {
    for (press_count[2] = 0; press_count[2] <= 3; ++press_count[2]) {
      for (press_count[3] = 0; press_count[3] <= 3; ++press_count[3]) {
        for (press_count[4] = 0; press_count[4] <= 3; ++press_count[4]) {
          for (press_count[5] = 0; press_count[5] <= 3; ++press_count[5]) {
            for (press_count[6] = 0; press_count[6] <= 3; ++press_count[6]) {
              for (press_count[7] = 0; press_count[7] <= 3; ++press_count[7]) {
                for (press_count[8] = 0; press_count[8] <= 3;
                     ++press_count[8]) {
                  for (press_count[9] = 0; press_count[9] <= 3;
                       ++press_count[9]) {
                    checkCombination();
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  bool temp = true;
  for (int i = 1; i <= 9; ++i) {
    for (int j = 0; j < best[i]; ++j) {
      if (!temp) fout << " ";

      fout << i;
      temp = false;
    }
  }
  fout << "\n";

  return 0;
}
