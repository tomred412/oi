/*
ID: dermotl1
LANG: C++
PROG: fence8
*/

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
#include <utility>
#include <vector>

using namespace std;

int n, r;
vector<int> boards;
vector<int> rails;
vector<int> sums;
vector<int> boards_left;
int boards_left_sum;
int extra;
int waste;
int smallest;

bool dfs(int i) {
  if (i < 0) return true;
  if (boards_left_sum < sums[i]) return false;

  int length = rails[i];
  int last_left_tried = -1;

  for (int j = 0; j < boards_left.size(); ++j) {
    int available = boards_left[j];
    if (available < length) continue;
    if (available == last_left_tried) continue;
    last_left_tried = available;

    int before = available;
    int after_cutting = before - length;

    boards_left[j] = after_cutting;
    boards_left_sum -= length;

    bool added_waste = false;
    int addded_waste_amount = 0;

    if (before >= smallest && after_cutting < smallest) {
      added_waste = true;
      addded_waste_amount = after_cutting;
      waste += after_cutting;
    }

    bool ok = false;
    if (waste <= extra) {
      ok = dfs(i - 1);
    }
    if (added_waste) waste -= addded_waste_amount;  // goback
    boards_left[j] = before;
    boards_left_sum += length;

    if (ok) return true;
    if (before == length) break;
  }
  return false;
}

bool canMakeRails(int m) {
  if (m == 0) return true;
  smallest = rails[0];

  boards_left.clear();
  int usable_boards_sum = 0;

  for (auto it : boards) {
    if (it >= smallest) {
      boards_left.push_back(it);
      usable_boards_sum += it;
    }
  }

  int rails_sum = sums[m - 1];
  if (usable_boards_sum < rails_sum) return false;

  sort(boards_left.begin(), boards_left.end(),
       [](int a, int b) { return a > b; });  // prune

  boards_left_sum = usable_boards_sum;
  extra = usable_boards_sum - rails_sum;  // to spare
  waste = 0;

  return dfs(m - 1);
}

int main() {
  ifstream fin("fence8.in");
  ofstream fout("fence8.out");

  fin >> n;
  boards.resize(n);
  for (int i = 0; i < n; ++i) {
    fin >> boards[i];
  }

  sort(boards.begin(), boards.end());

  fin >> r;
  for (int i = 0; i < r; ++i) {
    int temp;
    fin >> temp;
    if (temp <= boards.back()) rails.push_back(temp);
  }

  if (rails.empty()) {
    fout << "0\n";
    return 0;
  }

  sort(rails.begin(), rails.end());

  sums.resize(rails.size());
  int running = 0;
  for (int i = 0; i < rails.size(); ++i) {  // calculate sums for later
    running += rails[i];
    sums[i] = running;
  }

  int low = 0;
  int high = rails.size();
  while (low < high) {
    int mid = (low + high + 1) / 2;
    if (canMakeRails(mid))
      low = mid;
    else
      high = mid - 1;
  }

  fout << low << "\n";

  return 0;
}