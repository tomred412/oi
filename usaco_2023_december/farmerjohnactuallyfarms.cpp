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
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<long long> initial_plants(n);
    vector<long long> growth_plants(n);
    vector<int> targets_plants(n);

    for (int i = 0; i < n; ++i) {
      cin >> initial_plants[i];
    }
    for (int i = 0; i < n; ++i) {
      cin >> growth_plants[i];
    }
    for (int i = 0; i < n; ++i) {
      cin >> targets_plants[i];
    }
    vector<int> convert_target_to_plant(n);
    for (int i = 0; i < n; ++i) {
      convert_target_to_plant[i] = i;
    }
    sort(convert_target_to_plant.begin(), convert_target_to_plant.end(),
         [&](int i, int j) { return targets_plants[i] < targets_plants[j]; });

    long long lowest_days = 0;
    long long highest_days = numeric_limits<long long>::max();
    bool ok = true;

    for (int i = 0; i + 1 < n; ++i) {
      int tall = convert_target_to_plant[i];
      int shorts = convert_target_to_plant[i + 1];

      long long growth_dif = growth_plants[tall] - growth_plants[shorts];
      long long height_dif = initial_plants[shorts] - initial_plants[tall];

      if (growth_dif == 0) {
        if (!(initial_plants[tall] > initial_plants[shorts])) {
          ok = false;
          break;
        }
        continue;
      }

      if (growth_dif > 0) {
        long long quo = height_dif / growth_dif;
        long long rem = height_dif % growth_dif;

        if (rem != 0 && ((rem > 0) != (growth_dif > 0)))
          --quo;  // fix, but compare for correct growth and height

        long long min = quo + 1;
        if (min > lowest_days) lowest_days = min;
      } else {
        long long quo = height_dif / growth_dif;
        long long rem = height_dif % growth_dif;

        if (rem != 0 && ((rem > 0) == (growth_dif > 0))) ++quo;

        long long max = quo - 1;
        if (max < highest_days) highest_days = max;
      }
    }
    if (!ok) {
      cout << "-1\n";
      continue;
    }
    if (lowest_days < 0) lowest_days = 0;
    if (lowest_days <= highest_days)
      cout << lowest_days << "\n";
    else
      cout << "-1\n";
  }
  return 0;
}