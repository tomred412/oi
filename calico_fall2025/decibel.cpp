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

string solve(string quiet) {
  vector<char> loud;
  for (int i = 0; i < quiet.size(); ++i) {
    if (quiet[i] >= 97 && quiet[i] <= 122) {
      loud.push_back(quiet[i] - 32);
    } else {
      loud.push_back(quiet[i]);
      loud.push_back(quiet[i] + 32);
    }
  }
  string answer(loud.begin(), loud.end());
  return answer;
}

long long score(string s) {
  long long answer = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] >= 97 && s[i] <= 122) {
      answer += s[i] - 96;
    } else {
      answer += s[i] - 38;
    }
  }
  return answer;
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
    for (int i = 0; i < k; ++i) {
      quiet = solve(quiet);
    }
    cout << score(quiet) << "\n";
  }
  return 0;
}