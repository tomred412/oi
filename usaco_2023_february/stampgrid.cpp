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

vector<string> rotate(vector<string> stamp) {  // 90 deg clockwise
  int k = stamp.size();
  vector<string> result(k, string(k, '.'));
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      result[j][k - i - 1] = stamp[i][j];
    }
  }
  return result;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<string> target(n);

    for (int i = 0; i < n; ++i) {
      cin >> target[i];
    }

    int k;
    cin >> k;
    vector<string> stamp(k);
    for (int i = 0; i < k; ++i) {
      cin >> stamp[i];
    }

    vector<vector<string>> rotations(4);
    rotations[0] = stamp;
    for (int i = 1; i < 4; ++i) {
      rotations[i] = rotate(rotations[i - 1]);
    }
    vector<vector<bool>> can_paint(n, vector<bool>(n, false));

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j + k <= n; ++j) {
        for (int q = 0; q + k <= n; ++q) {
          bool good = true;
          for (int x = 0; x < k && good; ++x) {
            for (int y = 0; y < k && good; ++y) {
              if (rotations[i][x][y] == '*' && target[j + x][q + y] != '*')
                good = false;
            }
          }
          if (!good) continue;
          for (int x = 0; x < k; ++x) {
            for (int y = 0; y < k; ++y) {
              if (rotations[i][x][y] == '*') can_paint[j + x][q + y] = true;
            }
          }
        }
      }
    }
    bool ok = true;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (target[i][j] == '*' && !can_paint[i][j]) ok = false;
      }
    }
    cout << (ok ? "YES\n" : "NO\n");
  }
  return 0;
}