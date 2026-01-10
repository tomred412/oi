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

struct aircon {
  int start, end, power, cost;
};

int n, m;
int needed_stalls[101];
vector<aircon> acs;

int min_money = numeric_limits<int>::max();

void solve(int index, int cost, vector<int> cooling) {
  if (index == m) {
    bool good = true;
    for (int i = 1; i <= 100; ++i) {
      if (cooling[i] < needed_stalls[i]) {
        good = false;
        break;
      }
    }
    if (good) {
      min_money = min(min_money, cost);
    }
    return;
  }

  solve(index + 1, cost, cooling);
  vector<int> next_cooling = cooling;

  for (int i = acs[index].start; i <= acs[index].end; ++i) {
    next_cooling[i] += acs[index].power;
  }

  solve(index + 1, cost + acs[index].cost, next_cooling);
}

int main() {
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int s, t, c;
    cin >> s >> t >> c;
    for (int j = s; j <= t; j++) {
      needed_stalls[j] = c;
    }
  }

  for (int i = 0; i < m; i++) {
    int a, b, p, mo;
    cin >> a >> b >> p >> mo;
    aircon temp;
    temp.start = a;
    temp.end = b;
    temp.power = p;
    temp.cost = mo;
    acs.push_back(temp);
  }

  vector<int> cooling(101, 0);
  solve(0, 0, cooling);

  cout << min_money << "\n";

  return 0;
}