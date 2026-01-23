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

long long a, b, ca, cb, fa;

long long findMaxA(long long x, long long b_chips) {
  long long conversion = (b_chips / cb) * ca;
  long long spent = b_chips - b;
  return a + x + conversion - spent;
}

bool ok(long long x) {
  long long start = b;
  long long end = b + x;

  long long worst = findMaxA(x, end);

  long long t = end - (end % cb) - 1;
  if (t >= start) worst = min(worst, findMaxA(x, t));

  t = start + (cb - 1 - (start % cb) + cb) % cb;
  if (t <= end) worst = min(worst, findMaxA(x, t));

  return worst >= fa;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> a >> b >> ca >> cb >> fa;

    if (findMaxA(0, b) >= fa) {
      cout << 0 << "\n";
      continue;
    }

    long long low = 0;
    long long hi = max(fa, (fa + ca - 1) / ca * cb - b) + ca * cb + 1;
    long long answer = hi;

    while (low <= hi) {
      long long mid = low + (hi - low) / 2;
      if (ok(mid)) {
        answer = mid;
        hi = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    cout << answer << "\n";
  }
  return 0;
}
