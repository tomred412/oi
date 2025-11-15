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
    string e;
    cin.ignore();
    getline(cin, e);
    int year, month, day;
    cin >> year >> month >> day;
    if (year < 2026) {
      cout << "we got " << e << " before gta6\n";
    } else if (year == 2026 && month < 11) {
      cout << "we got " << e << " before gta6\n";
    } else if (year == 2026 && month == 11 && day < 19) {
      cout << "we got " << e << " before gta6\n";
    } else {
      cout << "we got gta6 before " << e << "\n";
    }
  }
  return 0;
}