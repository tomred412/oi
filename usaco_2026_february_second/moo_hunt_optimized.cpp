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

// brute force
int n, k;
vector<int> x, y, z;  // 0 based
char board[20];
int required_count[20];  // number of moves that MUST be here (M)

int best_score = -1;
long long best_boards_count = 0;

int countBoard() {
  int points = 0;
  for (int i = 0; i < k; ++i) {
    if (board[x[i]] == 'M' && board[y[i]] == 'O' && board[z[i]] == 'O')
      ++points;
  }
  return points;
}

void solve(int index, int max_remaining) {
  if (max_remaining < best_score) return;

  if (index == n) {
    int current_points = countBoard();
    if (current_points > best_score) {
      best_score = current_points;
      best_boards_count = 1;
    } else if (current_points == best_score) {
      ++best_boards_count;
    }
    return;
  }
  board[index] = 'M';
  solve(index + 1, max_remaining);

  board[index] = 'O';
  solve(index + 1, max_remaining - required_count[index]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;

  for (int i = 0; i < k; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    x.push_back(a - 1);
    y.push_back(b - 1);
    z.push_back(c - 1);
  }

  for (int i = 0; i < k; ++i) {
    ++required_count[x[i]];
  }

  solve(0, k);

  cout << best_score << " " << best_boards_count << "\n";

  return 0;
}
