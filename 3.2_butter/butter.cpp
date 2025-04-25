/*
ID: dermotl1
LANG: C++
PROG: butter
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct adjacency {
  int near;
  int cost;
};

int int_infinity = numeric_limits<int>::max();
long long long_infinity = numeric_limits<long long>::max();

vector<vector<adjacency> > adj;
int p;

vector<long long> solve(int start) {  // distance from start to finish
  vector<long long> dist(p, long_infinity);
  vector<bool> visited(p, false);
  priority_queue<pair<long long, int> >
      unvisited;  // long long = distance, int = vertex

  unvisited.push(make_pair(0, start));

  dist[start] = 0;

  while (!unvisited.empty()) {
    int a = unvisited.top().second;
    unvisited.pop();

    if (visited[a]) continue;
    visited[a] = true;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i].near;
      int weight = adj[a][i].cost;
      if (!visited[b] && dist[a] + weight < dist[b]) {
        dist[b] = dist[a] + weight;
        unvisited.push(make_pair(
            -dist[b], b));  // put a negative so it's max heap (min heap)
      }
    }
  }

  return dist;
}

int main() {
  ifstream fin("butter.in");
  ofstream fout("butter.out");

  int n, c;
  fin >> n >> p >> c;
  adj.resize(p);

  vector<int> cow_positions(n);
  for (int i = 0; i < n; ++i) {
    fin >> cow_positions[i];
    cow_positions[i]--;
  }

  for (int i = 0; i < c; ++i) {
    int x, y, cost;
    fin >> x >> y >> cost;
    x--;
    y--;
    adjacency temp;
    temp.near = y;
    temp.cost = cost;
    adj[x].push_back(temp);
    temp.near = x;
    adj[y].push_back(temp);
  }
  vector<int> cow_count(p, 0);
  for (int i = 0; i < n; ++i) {
    cow_count[cow_positions[i]]++;
  }

  long long min_dist = long_infinity;
  for (int i = 0; i < p; ++i) {
    vector<long long> dist = solve(i);

    long long total = 0;
    for (int j = 0; j < p; ++j) {
      total += dist[j] * cow_count[j];
    }
    min_dist = min(min_dist, total);
  }
  fout << min_dist << "\n";

  return 0;
}
