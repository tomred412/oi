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
  long long t;
  cin >> n >> t;

  vector<long long> days;
  vector<long long> deliveries;

  for (int i = 0; i < n; ++i) {
    long long temp;
    cin >> temp;
    days.push_back(temp);
    cin >> temp;
    deliveries.push_back(temp);
  }

  long long current_day = 1;
  long long current_hay = 0;
  long long eaten = 0;

  for (int i = 0; i < n; ++i) {
    long long gap = days[i] - current_day;
    long long eat_now;
    if (current_hay < gap)
      eat_now = current_hay;
    else
      eat_now = gap;

    eaten += eat_now;
    current_hay -= eat_now;

    current_day = days[i];
    current_hay += deliveries[i];
  }

  if (current_day <= t) {
    long long remaining_days = t - current_day + 1;
    long long eat_now;
    if (current_hay < remaining_days)
      eat_now = current_hay;
    else
      eat_now = remaining_days;

    eaten += eat_now;
  }

  cout << eaten << "\n";

  return 0;
}