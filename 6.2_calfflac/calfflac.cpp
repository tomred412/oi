/*
ID: dermotl1
LANG: C++
PROG: calfflac
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
#include <utility>
#include <vector>

using namespace std;

int main() {
  ifstream fin("calfflac.in");
  ofstream fout("calfflac.out");

  string original;
  char temp;
  while (fin.get(temp)) {
    original += temp;
  }
  string clean;
  vector<int> original_index;

  for (int i = 0; i < original.length(); ++i) {
    if (isalpha(original[i])) {
      clean += tolower(original[i]);
      original_index.push_back(i);
    }
  }
  int max = 0;
  int max_start_clean = 0;
  for (int i = 0; i < clean.length(); ++i) {
    // Odd:
    int left = i, right = i;
    while (left >= 0 && right < clean.length() && clean[left] == clean[right]) {
      if (right - left + 1 > max) {
        max = right - left + 1;
        max_start_clean = left;
      }
      --left;
      ++right;
    }
    // Even:
    left = i, right = i + 1;
    while (left >= 0 && right < clean.length() && clean[left] == clean[right]) {
      if (right - left + 1 > max) {
        max = right - left + 1;
        max_start_clean = left;
      }
      --left;
      ++right;
    }
  }

  int original_start = original_index[max_start_clean];
  int max_end_clean = max_start_clean + max - 1;
  int original_end = original_index[max_end_clean];

  string answer =
      original.substr(original_start, original_end - original_start + 1);
  fout << max << "\n" << answer << "\n";
}