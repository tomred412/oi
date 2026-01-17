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
  int n, k, q;

  cin >> n >> k >> q;
  int w = n - k + 1;

  vector<vector<long long>> grid(n, vector<long long>(n, 0));
  vector<vector<long long>> sums(w, vector<long long>(w, 0));

  long long answer = 0;

  for (int i = 0; i < q; ++i) {
    int r, c, v;
    cin >> r >> c >> v;
    --r;
    --c;

    long long change = (long long)v - grid[r][c];
    grid[r][c] = v;

    if (change != 0) {
      int start_i = max(0, r - k + 1);
      int end_i = min(r, n - k);
      int start_j = max(0, c - k + 1);
      int end_j = min(c, n - k);

      for (int j = start_i; j <= end_i; ++j) {
        for (int p = start_j; p <= end_j; ++p) {
          sums[j][p] += change;
          if (sums[j][p] > answer) answer = sums[j][p];
        }
      }
    }
    cout << answer << "\n";
  }
  return 0;
}