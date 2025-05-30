/*
ID: dermotl1
LANG: C++
PROG: buylow
*/

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

void add(vector<int> &a, vector<int> &b, vector<int> &c) {
  int carry = 0;
  int n = max(a.size(), b.size());
  c.clear();
  c.reserve(n + 1);
  for (int i = 0; i < n; ++i) {
    int a1 = 0;
    if (i < a.size()) {
      a1 = a[i];
    }
    int b1 = 0;
    if (i < b.size()) {
      b1 = b[i];
    }
    int sum = a1 + b1 + carry;
    c.push_back(sum % 10);
    carry = sum / 10;
  }
  if (carry > 0) {
    c.push_back(carry);
  }
}

void subtract(vector<int> &a, vector<int> &b, vector<int> &c) {
  int borrow = 0;
  int n = max(a.size(), b.size());
  c.assign(n, 0);
  int last = -1;
  for (int i = 0; i < n; ++i) {
    int a1 = 0;
    if (i < a.size()) {
      a1 = a[i];
    }
    int b1 = 0;
    if (i < b.size()) {
      b1 = b[i];
    }
    int d = a1 - b1 - borrow;
    if (d < 0) {
      d += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }
    c[i] = d;
    if (d != 0) {
      last = i;
    }
  }
  int news;
  if (last >= 0) {
    news = last + 1;
  } else {
    news = 1;
  }
  c.resize(news);
}

int main() {
  ifstream fin("buylow.in");
  ofstream fout("buylow.out");

  int n;
  fin >> n;
  vector<long long> price(n);

  for (int i = 0; i < n; ++i) {
    fin >> price[i];
  }

  vector<long long> longest_sequence(n, 1);
  vector<vector<int> > counts(n, vector<int>(1, 1));  // sequences that end at i
  int best = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = i - 1; j >= 0; --j) {
      if (price[j] > price[i]) {
        if (longest_sequence[j] + 1 > longest_sequence[i]) {
          longest_sequence[i] = longest_sequence[j] + 1;
        }
      }
    }
    if (longest_sequence[i] > best) best = longest_sequence[i];
  }

  for (int i = 0; i < n; ++i) {
    if (longest_sequence[i] == 1) {
      counts[i][0] = 1;
    } else {
      counts[i].clear();
      int last = -1;
      int find = longest_sequence[i] - 1;
      for (int j = i - 1; j >= 0; --j) {
        if (price[j] > price[i] && price[j] != last &&
            longest_sequence[j] == find) {
          vector<int> temp;
          add(counts[i], counts[j], temp);
          counts[i].swap(temp);
          last = price[j];
        }
      }
    }
  }

  long long maxl = 0;
  for (int i = 0; i < n; ++i) {
    if (longest_sequence[i] > maxl) {
      maxl = longest_sequence[i];
    }
  }

  set<long long> seens;
  vector<int> total(1, 0);

  for (int i = n - 1; i >= 0; --i) {
    if (longest_sequence[i] == maxl && seens.count(price[i]) == 0) {
      vector<int> temp;
      add(total, counts[i], temp);
      total.swap(temp);
      seens.insert(price[i]);
    }
  }

  fout << maxl << " ";
  int i = total.size() - 1;
  while (i > 0 && total[i] == 0) {
    i--;
  }
  while (i >= 0) {
    fout << total[i];
    i--;
  }
  fout << "\n";
}