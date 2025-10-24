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
  int n;
  long long k;
  cin >> n >> k;

  vector<long long> days(n);
  for (int i = 0; i < n; ++i) {
    cin >> days[i];
  }

  long long total_cost = k + 1;
  long long current_length = 1;

  for (int i = 1; i < n; ++i) {
    long long gap = days[i] - days[i - 1];
    if (gap <= k) {
      current_length += gap;
    } else {
      total_cost += current_length + k;
      current_length = 1;
    }
  }
  total_cost += current_length - 1;
  cout << total_cost << "\n";

  return 0;
}