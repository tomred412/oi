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

long long score(string s, int k) {
  long long count_upper[27] = {0};
  long long count_lower[27] = {0};

  for (auto it : s) {
    if (it >= 97 && it <= 122) {
      ++count_lower[it - 97];
    } else {
      ++count_upper[it - 65];
    }
  }

  for (int i = 0; i < k; ++i) {
    long long temp_lower[27] = {0};
    long long temp_upper[27] = {0};

    for (int i = 0; i < 26; ++i) {
      temp_upper[i] = (count_lower[i] + count_upper[i]) % 998244353;
      temp_lower[i] = count_upper[i];
    }
    copy(temp_lower, temp_lower + 27, count_lower);
    copy(temp_upper, temp_upper + 27, count_upper);
  }

  long long answer = 0;
  for (int i = 0; i < 26; ++i) {
    answer = (answer + count_lower[i] * (i + 1)) % 998244353;
    answer = (answer + count_upper[i] * (i + 27)) % 998244353;
  }
  return answer % 998244353;
}

int main() {
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    string quiet;
    int k;
    cin >> quiet >> k;
    cout << score(quiet, k) << "\n";
  }
  return 0;
}