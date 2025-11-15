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
    int l;
    long long n;
    string s;
    cin >> l >> n >> s;

    long long fries = 0;
    int depth = 0;

    for (auto it : s) {
      if (it == '(')
        ++depth;
      else if (it == ')')
        --depth;
      else if (it == '|') {
        if (depth <= n) fries = (fries + 1) % 1000000001;
      } else if (it == 'O') {
        fries = (2 * fries) % 1000000001;
      }
    }
    cout << fries << "\n";
  }
  return 0;
}