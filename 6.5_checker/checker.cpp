/*
ID: dermotl1
LANG: C++
PROG: checker
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
bool row_used[14];
bool first_diagonal[30];   //\, row + col
bool second_diagonal[30];  // /, row - col + (n - 1)
int positions[14];
vector<vector<int>> solution;

void placeHere(int col) {
  if (col == n) {
    vector<int> temp(n);
    for (int i = 0; i < n; ++i) {
      temp[i] = positions[i];
    }

    solution.push_back(temp);

    return;
  }

  for (int i = 0; i < n; ++i) {
    int first_d = i + col;
    int second_d = i - col + (n - 1);

    if (!row_used[i] && !first_diagonal[first_d] &&
        !second_diagonal[second_d]) {
      row_used[i] = true;
      first_diagonal[first_d] = true;
      second_diagonal[second_d] = true;

      positions[col] = i + 1;
      placeHere(col + 1);

      row_used[i] = false;
      first_diagonal[first_d] = false;
      second_diagonal[second_d] = false;
    }
  }
}

int main() {
  ifstream fin("checker.in");
  ofstream fout("checker.out");

  fin >> n;
  placeHere(0);

  sort(solution.begin(), solution.end());

  int printed = solution.size() < 3 ? solution.size() : 3;

  for (int i = 0; i < printed; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j) fout << " ";
      fout << solution[i][j];
    }
    fout << "\n";
  }
  fout << solution.size() << "\n";

  return 0;
}