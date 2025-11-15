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

int getDrift(const string& s,
             const int& index) {  // 0 up, 1 down, 2 left, 3 right
  if (s[index % s.length()] == 'U') return 0;
  if (s[index % s.length()] == 'D') return 1;
  if (s[index % s.length()] == 'L') return 2;
  return 3;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int grid[n][m];
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> grid[i][j];
      }
    }
  }
  return 0;
}