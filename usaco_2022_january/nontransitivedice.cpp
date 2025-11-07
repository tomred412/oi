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

bool beats(vector<int> x, vector<int> y) {
  int wins = 0;
  int losses = 0;
  for (auto i : x) {
    for (auto j : y) {
      if (i > j) ++wins;
      if (i < j) ++losses;
    }
  }
  return wins > losses;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    vector<int> a(4);
    vector<int> b(4);
    for (int i = 0; i < 4; ++i) {
      cin >> a[i];
    }
    for (int i = 0; i < 4; ++i) {
      cin >> b[i];
    }
    bool a_b = beats(a, b);
    bool b_a = beats(b, a);

    if (a_b == b_a) {
      cout << "no\n";
      continue;
    }

    bool yes = false;
    for (int i = 1; i <= 10 && !yes; i++) {
      for (int j = 1; j <= 10 && !yes; j++) {
        for (int l = 1; l <= 10 && !yes; l++) {
          for (int m = 1; m <= 10 && !yes; m++) {
            vector<int> c = {i, j, l, m};
            if (a_b) {
              if (beats(b, c) && beats(c, a)) yes = true;
            } else {
              if (beats(c, b) && beats(a, c)) yes = true;
            }
          }
        }
      }
    }
    cout << (yes ? "yes\n" : "no\n");
  }

  return 0;
}