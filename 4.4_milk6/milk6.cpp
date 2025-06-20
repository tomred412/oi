/*
ID: dermotl1
LANG: C++
PROG: milk6
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

long long capacity[35][35];  // how much left from x to y
long long original_capacity[35][35];
long long max_flow[35];
long long previous_node[35];
bool visited[35];
long long n, m;  // warehouses, routes

struct Path {
  int from;
  int to;
  int cost;
  int number;
};
Path paths[1001];

long long Solve(int source, int sink) {
  long long total_flow = 0;
  while (true) {
    memset(max_flow, 0, sizeof(max_flow));
    memset(visited, false, sizeof(visited));
    memset(previous_node, -1, sizeof(previous_node));

    queue<int> path;
    path.push(source);
    visited[source] = true;

    max_flow[source] = numeric_limits<long long>::max();

    while (!path.empty()) {
      int current = path.front();  // this one is different from reconstruction
      path.pop();

      for (int i = 1; i <= n; ++i) {
        if (!visited[i] && capacity[current][i] > 0) {
          visited[i] = true;
          previous_node[i] = current;
          max_flow[i] = min(max_flow[current], capacity[current][i]);
          path.push(i);
        }
      }
    }
    if (!visited[sink]) break;  // if there is no flow to sink

    long long path_flow = max_flow[sink];
    total_flow += path_flow;
    int current_node = sink;

    while (current_node != source) {
      int next_node = previous_node[current_node];
      capacity[next_node][current_node] -= path_flow;
      capacity[current_node][next_node] += path_flow;
      current_node = next_node;
    }
  }
  return total_flow;
}

int main() {
  ifstream fin("milk6.in");
  ofstream fout("milk6.out");

  fin >> n >> m;

  int x, y, z;
  for (int i = 0; i < m; ++i) {
    fin >> x >> y >> z;
    paths[i].from = x;
    paths[i].to = y;
    paths[i].cost = z * 1001 + 1;
    paths[i].number = i + 1;
    original_capacity[x][y] += z * 1001 + 1;
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      capacity[i][j] = original_capacity[i][j];
    }
  }

  long long total_cost = Solve(1, n);

  vector<int> answer;

  for (int i = 0; i < m; ++i) {
    x = paths[i].from;
    y = paths[i].to;
    z = paths[i].cost;

    if (total_cost == original_capacity[x][y] && original_capacity[x][y] == z) {
      fout << total_cost / 1001 << " 1\n" << i + 1 << "\n";
      return 0;
    }

    original_capacity[x][y] -= z;

    for (int oo = 1; oo <= n; ++oo) {
      for (int j = 1; j <= n; ++j) {
        capacity[oo][j] = original_capacity[oo][j];
      }
    }

    long long total_cost2 = Solve(1, n);

    if (total_cost2 == total_cost - z) {
      answer.push_back(i + 1);
    }
    original_capacity[x][y] += z;
  }

  fout << total_cost / 1001 << " " << answer.size() << "\n";
  for (int i = 0; i < answer.size(); ++i) {
    fout << answer[i] << "\n";
  }

  return 0;
}
