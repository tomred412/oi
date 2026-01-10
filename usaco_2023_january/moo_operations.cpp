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
  int q;
  cin >> q;
  while (q--) {
    string s;
    cin >> s;

    if (s.length() < 3) {
      cout << "-1\n";
      continue;
    }

    int answer = -1;
    for (int i = 0; i <= s.length() - 3; ++i) {
      int current = 0;
      if (s[i + 1] == 'O') {
        if (s[i] == 'O') ++current;
        if (s[i + 2] == 'M') ++current;

        if (answer == -1 || current < answer) answer = current;
      }
    }

    if (answer == -1)
      cout << "-1\n";
    else
      cout << (s.length() - 3) + answer << "\n";
  }

  return 0;
}