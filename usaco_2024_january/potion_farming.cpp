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

vector<vector<int>> adj;
vector<int> potions;
vector<int> no_children;
vector<int> collected;

void dfs(int current, int parent) {
  bool has_no_children = true;

  for (auto it : adj[current]) {
    if (it == parent) continue;
    has_no_children = false;

    dfs(it, current);

    no_children[current] += no_children[it];
    collected[current] += collected[it];
  }

  if (has_no_children) no_children[current] = 1;

  collected[current] =
      min(no_children[current], collected[current] + potions[current]);
}

int main() {
  int n;
  cin >> n;

  vector<int> input(n + 1);
  adj.resize(n + 1);

  for (int i = 1; i <= n; ++i) {
    cin >> input[i];
  }

  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  int no_children_count = 0;
  for (int i = 2; i <= n; ++i) {
    if (adj[i].size() == 1) ++no_children_count;
  }

  potions.resize(n + 1);
  no_children.resize(n + 1);
  collected.resize(n + 1);

  for (int i = 0; i < n + 1; ++i) {
    potions[i] = 0;
    no_children[i] = 0;
    collected[i] = 0;
  }

  for (int i = 1; i <= no_children_count; ++i) {
    ++potions[input[i]];
  }

  dfs(1, 0);

  cout << collected[1] << "\n";

  return 0;
}
