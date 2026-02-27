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

struct card {
  int number;
  int cost;

  bool operator<(const card& other) const {
    if (cost != other.cost) return cost < other.cost;
    return number < other.number;
  }
};

int n, h, k, q;

vector<int> hand;
queue<int> draw;

vector<long long> win_time;
long long win_sum;

void simulate(vector<int> cards_cost, vector<bool> is_win) {
  for (int i = h + 1; i <= n; ++i) {
    draw.push(i);
  }

  set<card> wins_in_hand;
  set<card> normal_in_hand;

  for (int i = 1; i <= h; ++i) {
    card temp;
    temp.number = i;
    temp.cost = cards_cost[i];

    if (is_win[i])
      wins_in_hand.insert(temp);
    else
      normal_in_hand.insert(temp);
  }

  long long time = 0;
  long long spent = 0;

  while (win_time.size() < k) {  // we only need to simulate k

    card now;

    bool played_win = false;

    if (!wins_in_hand.empty()) {
      now = *wins_in_hand.begin();
      wins_in_hand.erase(wins_in_hand.begin());
      played_win = true;
    } else {
      now = *normal_in_hand.begin();
      normal_in_hand.erase(normal_in_hand.begin());
    }

    time = max(time + 1, spent + now.cost);
    spent += now.cost;

    if (played_win) {
      win_time.push_back(time);
    }

    int new_number = draw.front();
    draw.pop();

    card next;
    next.number = new_number;
    next.cost = cards_cost[new_number];

    if (is_win[new_number]) {
      wins_in_hand.insert(next);
    } else {
      normal_in_hand.insert(next);
    }

    draw.push(now.number);
  }
  win_sum = 0;
  for (int i = 1; i <= n; ++i) {
    if (is_win[i]) {
      win_sum += cards_cost[i];
    }
  }
}

long long answerQuery(long long t) {
  if (t < win_time.front()) return 0;
  if (t < win_time.back())
    return upper_bound(win_time.begin(), win_time.end(), t) - win_time.begin();

  long long extra = (t - win_time.back()) / win_sum;
  return k + extra;
}

int main() {
  cin >> n >> h;
  vector<int> cards_cost(n + 1);

  for (int i = 1; i <= n; ++i) {
    cin >> cards_cost[i];
  }

  cin >> k;
  vector<bool> is_win(n + 1, false);

  for (int i = 0; i < k; ++i) {
    int temp;
    cin >> temp;
    is_win[temp] = true;
  }

  cin >> q;
  simulate(cards_cost, is_win);

  while (q--) {
    long long t;
    cin >> t;
    cout << answerQuery(t) << "\n";
  }
  return 0;
}