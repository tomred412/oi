#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> freq(n + 1);

    for (int i = 0; i < n; ++i) {
      int a;
      cin >> a;
      freq[a]++;
    }

    vector<int> heights;

    for (int i = 1; i <= n; ++i) {
      if (freq[i] >= 2) {
        heights.push_back(i);
      }
    }
    int ans = 0;
    bool bol = true;
    for (int i = n; i > 0; --i) {
      if (freq[i] == 0) continue;
      if (bol) {
        ans++;
      } else if (freq[i] >= 2) {
        ans = ans + 2;
      }
      bol = false;
    }
    cout << ans << "\n";
  }
  return 0;
}
