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
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<long long> hunger(n + 1);
    long long total = 0;
    for (int i = 1; i <= n; ++i) {
      cin >> hunger[i];
      total += hunger[i];
    }
    vector<long long> sums(n + 1, 0);
    int sign = 1;
    for (int i = 1; i <= n; ++i) {
      sums[i] = sums[i - 1] + sign * hunger[i];
      sign = -sign;
    }
    bool ok = true;
    long long x = 0;

    if (n % 2 == 0) {
      if (sums[n] != 0) ok = false;

      long long min_odd = numeric_limits<long long>::max();
      for (int i = 1; i < n; i += 2) {
        min_odd = min(min_odd, sums[i]);
      }

      for (int i = 2; i < n; i += 2) {
        if (sums[i] > 0) ok = false;
      }

      if (min_odd < 0) ok = false;
      x = min_odd;
    } else {
      x = sums[n];
      if (x < 0) ok = false;

      for (int i = 2; i < n; i += 2) {
        if (sums[i] > 0) ok = false;
      }

      for (int i = 1; i < n; i += 2) {
        if (x > sums[i]) ok = false;
      }
    }
    for (int i = 1; i <= n && ok; i++) {
      if (hunger[i] < x) ok = false;
    }
    if (!ok)
      cout << "-1\n";
    else
      cout << total - (long long)n * x << "\n";
  }

  return 0;
}