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

  int pos[3][3];

  // COW
  pos[0][0] = 0;
  pos[0][1] = 1;
  pos[0][2] = 2;
  // OWC
  pos[1][0] = 2;
  pos[1][1] = 0;
  pos[1][2] = 1;
  // WCO
  pos[2][0] = 1;
  pos[2][1] = 2;
  pos[2][2] = 0;

  cin >> t >> k;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    if (n % 2 == 1) {
      cout << "-1\n";
      continue;
    }

    int h = n / 2;
    vector<int> type(n);

    for (int i = 0; i < n; ++i) {
        }
  }

  return 0;
}