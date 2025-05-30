#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int solve(int solving) {
  int greater = 1;
  for (int i = 0; i < 9; ++i) {
    if (greater <= solving)
      greater *= 10;
    else
      break;
  }
  int answer = 0;
  long long low = 45;
  long long range = 5;

  while (low <= solving) {
    int high = low + range - 1;
    if (high > solving) {
      answer += solving - low + 1;
    } else {
      answer += range;
    }
    low = low * 10 - 5;
    range = range * 10 + 5;
  }
  return answer;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int n;
    cin >> n;
    cout << solve(n) << "\n";
  }

  return 0;
}