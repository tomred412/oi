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

int main() {
  int n, q;
  cin >> n >> q;
  vector<long long> original_prices(n + 1);  // 1 based
  vector<long long> queries(q);
  long long largest_query = 0;

  for (int i = 1; i <= n; ++i) {
    cin >> original_prices[i];
  }

  for (int i = 0; i < q; ++i) {
    cin >> queries[i];
    largest_query = max(largest_query, queries[i]);  // to save time later
  }

  // make a bigger bucket never more expensive than 2 smaller ones (delete the
  // expensive ones) to make it easier
  for (int i = 2; i <= n; ++i) {
    original_prices[i] = min(original_prices[i], 2 * original_prices[i - 1]);
  }

  vector<long long> buckets;
  vector<long long> costs;  // new, caclulated ones
  long long current_bucket = 1;

  for (int i = 1; i <= n; ++i) {
    buckets.push_back(current_bucket);
    costs.push_back(original_prices[i]);

    if (current_bucket > largest_query)
      break;  // because the other ones are more expensive and more, so we dont
    // need them, but we need this one

    current_bucket *= 2;
  }

  for (int i = 0; i < q; ++i) {
    long long current_cost = 0;
    long long needed = queries[i];
    long long best = numeric_limits<long long>::max();

    for (int i = buckets.size() - 1; i >= 0;
         --i) {  // biggest to smallest, biggest always cheaper than combination

      long long use = needed / buckets[i];
      current_cost += use * costs[i];
      needed -= use * buckets[i];

      long long prospect_best;
      if (needed > 0)
        prospect_best = current_cost + costs[i];
      else
        prospect_best = current_cost;

      best = min(best, prospect_best);
    }
    cout << best << "\n";
  }
  return 0;
}