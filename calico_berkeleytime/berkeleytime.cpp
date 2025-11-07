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
    int temp;
    cin >> temp;
    if (temp == 0) {
      cout << "haha good one\n";
    } else if (temp >= 10 && temp <= 170) {
      for (int i = 0; i < temp / 10; ++i) {
        cout << "berkeley";
      }
      cout << "time\n";
    } else {
      cout << "canceled\n";
    }
  }
  return 0;
}