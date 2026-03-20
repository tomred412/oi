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
  cin >> n;

  vector<long long> capacity(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> capacity[i];
  }

  int q;
  cin >> q;

  while (q--) {
    int index;
    long long v, t;
    cin >> index >> v >> t;

    capacity[index] = v;

    vector<long long> milk(n + 1, 0);
    vector<bool> flipped(n + 1, false);
    long long pool = 0;

    for (long long i = 1; i <= t; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (!flipped[j]) continue;
        long long amount = milk[j];
        milk[j] = 0;

        if (amount == 0) continue;
        if (j == n) {
          pool += amount;
        } else {
          long long remaining = capacity[j + 1] - milk[j + 1];
          if (remaining > 0) {
            milk[j + 1] += min(remaining, amount);
          }
        }
      }

      long long arriving = 1;
      for (int j = 1; j <= n && arriving > 0; ++j) {
        if (flipped[j]) {
          arriving = 0;
          break;
        }

        long long remaining = capacity[j] - milk[j];
        if (remaining > 0) {
          milk[j] += min(remaining, arriving);
          arriving -= min(arriving, remaining);
        }

        if (arriving > 0 && j == n) arriving = 0;
      }

      for (int j = 1; j <= n; ++j) {
        flipped[j] = (milk[j] == capacity[j]);
      }
    }
    cout << pool << "\n";
  }
}