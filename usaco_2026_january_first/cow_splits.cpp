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
  int k;

  cin >> t >> k;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    if (n % 2 == 1) {
      cout << "-1\n";
      continue;
    }

    vector<int> answer(3 * n, 1);
    if (s.substr(0, s.length() / 2) ==
        s.substr(s.length() / 2, s.length() / 2)) {
      cout << "1\n";
      for (int i = 0; i < 3 * n - 1; ++i) {
        cout << answer[i] << " ";
      }
      cout << "1\n";
      continue;
    }

    for (int i = 0; i < n / 2; ++i) {
      int start = i * 3;
      int end = (i + n / 2) * 3;

      bool good = true;
      for (int j = 0; j < 3; ++j) {
        if (s[start + j] != s[end + j]) {
          good = false;
          break;
        }
      }

      if (good) continue;

      if (s[start] == s[end + 1] && s[start + 1] == s[end + 2]) {
        answer[start + 2] = 2;
        answer[end] = 2;
      } else if (s[start + 1] == s[end] && s[start + 2] == s[end + 1]) {
        answer[start] = 2;
        answer[end + 2] = 2;
      }
    }

    cout << "2\n";
    for (int i = 0; i < s.length() - 1; ++i) {
      cout << answer[i] << " ";
    }
    cout << answer[s.length() - 1] << "\n";
  }

  return 0;
}
