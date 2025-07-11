/*
ID: dermotl1
LANG: C++
PROG: milk4
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int q, p;
vector<int> pails;
vector<int> best;  // stores solution

bool CanUse(int q, vector<int>& pail_subset) {
  vector<bool> usable(q + 1, false);
  usable[0] = true;

  for (int i = 0; i <= q; ++i) {
    if (usable[i]) {
      for (int j = 0; j < pail_subset.size(); ++j) {
        int next = i + pail_subset[j];
        if (next <= q) usable[next] = true;
      }
    }
  }
  return usable[q];
}

void TryAll(int pos, int size, vector<int>& current) {
  if (current.size() == size) {
    if (CanUse(q, current)) {
      best = current;
    }
    return;
  }

  if (pos >= p || !best.empty()) return;

  current.push_back(pails[pos]);  // include the current one
  TryAll(pos + 1, size, current);
  current.pop_back();

  TryAll(pos + 1, size, current);  // dont include the current one
}

int main() {
  ifstream fin("milk4.in");
  ofstream fout("milk4.out");

  fin >> q >> p;
  for (int i = 0; i < p; ++i) {
    int temp;
    fin >> temp;
    pails.push_back(temp);
  }

  sort(pails.begin(), pails.end());

  for (int i = 1; i <= p; ++i) {
    vector<int> current;
    TryAll(0, i, current);
    if (!best.empty()) break;
  }

  fout << best.size();
  for (auto it : best) {
    fout << " " << it;
  }
  fout << "\n";

  return 0;
}
