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
  int t, k;
  cin >> t >> k;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;

    if (k == 0) {
      cout << "YES\n";  // its impossible to output no at all because the last
                        // letter isnt changed
      continue;
    } else {  // to solve the problem, you can go one at a time. backwards
      // because the last letters arent changed

      char answer[n];
      bool flip = false;  // use a bool to save time

      for (int i = n - 1; i >= 0; --i) {
        char c = s[i];

        if (flip) {
          if (c == 'O')
            c = 'M';
          else
            c = 'O';
        }
        if (c == 'M') {
          answer[i] = 'M';

        } else {
          answer[i] = 'O';
          flip = !flip;
        }
      }

      cout << "YES\n";
      for (int i = 0; i < n; ++i) {
        cout << answer[i];
      }
      cout << "\n";
    }
  }
  return 0;
}
