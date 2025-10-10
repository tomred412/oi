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
#include <utility>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<long long> heights(n);

  for (int i = 0; i < n; ++i) {
    cin >> heights[i];
  }
  for (int i = 0; i < m; ++i) {
    int temp;
    cin >> temp;
    int eaten = 0;

    for (int j = 0; j < n; ++j) {
      if (eaten >= temp) break;

      long long height = heights[j];
      if (height > temp) height = temp;

      if (height > eaten) {
        long long help = height - eaten;
        heights[j] += help;
        eaten += help;
      }
    }
  }
  for (auto it : heights) {
    cout << it << "\n";
  }
  return 0;
}