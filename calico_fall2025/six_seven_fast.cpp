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
    int k;
    cin >> k;
    cout << ((k % 3 == 0 || k == 1) ? "Oski\n" : "Big Ben\n");
  }
  return 0;
}