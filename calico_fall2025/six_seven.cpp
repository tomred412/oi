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

bool dfs(int turn, bool was_last_6, int player, int k,
         vector<vector<vector<int>>> &cache) {
  if (turn == k) return false;
  if (cache[turn][was_last_6][player] != -1)
    return cache[turn][was_last_6][player];

  bool next_last6 = true;
  int next_player6 = 1 - player;
  bool next6 = dfs(turn + 1, next_last6, next_player6, k, cache);
  if (!next6) {
    cache[turn][was_last_6][player] = 1;
    return true;
  }

  bool next_last7 = false;
  int next_player7;

  if (was_last_6) {
    next_player7 = player;
  } else {
    next_player7 = 1 - player;
  }

  bool next7 = dfs(turn + 1, next_last7, next_player7, k, cache);
  if (was_last_6) {
    if (next7) {
      cache[turn][was_last_6][player] = 1;
      return true;
    }
  } else {
    if (!next7) {
      cache[turn][was_last_6][player] = 1;
      return true;
    }
  }
  cache[turn][was_last_6][player] = 0;
  return false;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int k;
    cin >> k;
    vector<vector<vector<int>>> cache(
        k + 1, vector<vector<int>>(2, vector<int>(2, -1)));
    cout << ((dfs(1, false, 0, k, cache)) ? "Big Ben\n" : "Oski\n");
  }
  return 0;
}