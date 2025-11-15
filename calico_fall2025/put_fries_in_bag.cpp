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

string replace_all(string str, const string& from, const string& to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
  return str;
}

void solve() {
  int T;
  if (!(cin >> T)) return;

  for (int i = 0; i < T; ++i) {
    int L, N;
    if (!(cin >> L >> N)) return;

    string bag;
    cin >> bag;

    string a = bag;
    vector<int> fries;
    vector<int> bags;
    int layer = 0;

    for (int j = 0; j < 4; ++j) {
      bag = replace_all(bag, "O", a);
    }

    for (char b : bag) {
      if (b == '(') {
        layer += 1;
      } else if (b == ')') {
        layer -= 1;
      } else if (b == '|') {
        fries.push_back(layer);
      } else {
        bags.push_back(layer);
      }
    }

    int t = 0;

    for (int fry : fries) {
      if (fry <= N) {
        t += 1;
      }
    }

    cout << t << endl;
  }
}

int main() {
  solve();
  return 0;
}