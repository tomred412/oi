/*
ID: dermotl1
LANG: C++
PROG: theme
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

int original[5002];
int difference[5002];  // find the difference between each 2 notes so dont deal
                       // with transpose
int n;

bool CheckLengthExisting(int length) {
  for (int i = 0; i + length <= n - 1; ++i) {
    for (int j = length + i; j + length <= n; ++j) {
      if (abs(i - j) >= length + 1) {
        bool check = true;
        for (int q = 0; q < length; ++q) {
          if (difference[i + q] != difference[j + q]) {
            check = false;
            break;
          }
        }
        if (check) return true;
      }
    }
  }
  return false;
}

int main() {
  ifstream fin("theme.in");
  ofstream fout("theme.out");

  fin >> n;

  for (int i = 0; i < n; ++i) {
    fin >> original[i];
  }

  for (int i = 0; i < n - 1; ++i) {
    difference[i] = original[i + 1] - original[i];
  }

  int low = 4;
  int high = n - 1;
  int result = 0;

  while (low <= high) {
    int middle = (low + high) / 2;
    if (CheckLengthExisting(middle)) {
      result = middle;
      low = middle + 1;
    } else {
      high = middle - 1;
    }
  }

  if (result >= 4)
    fout << result + 1 << "\n";
  else
    fout << "0\n";

  return 0;
}