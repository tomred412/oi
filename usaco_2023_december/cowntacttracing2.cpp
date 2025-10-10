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
  cin >> n;
  string infect;
  cin >> infect;

  bool check = false;
  for (int i = 0; i < n; ++i) {
    if (infect[i] == '1') {
      check = true;
      break;
    }
  }
  if (check == false) {
    cout << "0\n";
    return 0;
  }

  int nights_passed =
      numeric_limits<int>::max();  // first half: number of nights
  int i = 0;
  while (i < n) {
    if (infect[i] == '0') {
      ++i;
      continue;
    }

    int j = i;
    while (j < n && infect[j] == '1') {
      ++j;
    }
    int length = j - i;
    bool left_edge = (i == 0);
    bool right_edge = (j == n);
    bool inside = !right_edge && !left_edge;
    if (inside) {
      nights_passed =
          min(nights_passed, ((length - 1) / 2));  // more and more precise
    } else {
      nights_passed = min(nights_passed, length - 1);
    }

    i = j;
  }

  int max_continuous = 2 * nights_passed + 1;
  i = 0;
  int answer = 0;
  while (i < n) {
    if (infect[i] == '0') {
      ++i;
      continue;
    }

    int j = i;
    while (j < n && infect[j] == '1') {
      ++j;
    }
    int length = j - i;
    answer += (length + max_continuous - 1) / max_continuous;

    i = j;
  }

  cout << answer << "\n";

  return 0;
}