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

int main() {
  int n;
  string breeds;
  cin >> n;
  cin >> breeds;

  vector<int> line(n);
  for (int i = 0; i < n; ++i) {
    cin >> line[i];
    --line[i];
  }

  int g_start = -1, g_end = -1;
  int h_start = -1, h_end = -1;

  for (int i = 0; i < n; i++) {
    if (breeds[i] == 'G') {
      if (g_start == -1) g_start = i;
      g_end = i;
    } else {
      if (h_start == -1) h_start = i;
      h_end = i;
    }
  }

  long long count = 0;

  if (line[g_start] >= g_end) {
    for (int i = 0; i < n; ++i) {
      if (breeds[i] == 'H') {
        if (i == h_start && (line[h_start] >= h_end))
          ++count;
        else if (i < g_start && line[i] >= g_start)
          ++count;
      }
    }
  }

  if (line[h_start] >= h_end) {
    for (int i = 0; i < n; ++i) {
      if (breeds[i] == 'G') {
        if (i == g_start && (line[g_start] >= g_end))
          ++count;
        else if (i < h_start && line[i] >= h_start)
          ++count;
      }
    }
  }

  if (line[g_start] >= g_end && line[h_start] >= h_end) --count;

  cout << count << "\n";

  return 0;
}