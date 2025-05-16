/*
ID: dermotl1
LANG: C++
PROG: ditch
*/

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int capacity[205][205];  // how much left from x to y
int max_flow[205];
int previous_node[205];
bool visited[205];
int n, m;

int solve(int source, int sink) {
  int total_flow = 0;
  while (true) {
    memset(max_flow, 0, sizeof(max_flow));
    memset(visited, false, sizeof(visited));
    memset(previous_node, -1, sizeof(previous_node));

    max_flow[source] = numeric_limits<int>::max();

    while (true) {
      int max_flows = 0;
      int max_loc = -1;

      for (int i = 1; i <= m; ++i) {
        if (!visited[i] && max_flow[i] > max_flows) {
          max_flows = max_flow[i];
          max_loc = i;
        }
      }
      if (max_loc == -1 || max_loc == sink) break;
      visited[max_loc] = true;

      for (int i = 1; i <= m; ++i) {
        if (max_flow[i] < min(max_flows, capacity[max_loc][i])) {
          previous_node[i] = max_loc;
          max_flow[i] = min(max_flows, capacity[max_loc][i]);
        }
      }
    }
    if (max_flow[sink] == 0) break;  // if there is no flow to sink

    int path_capacity = max_flow[sink];
    total_flow += path_capacity;

    int current_node = sink;
    while (current_node != source) {
      int next_node = previous_node[current_node];
      capacity[next_node][current_node] -= path_capacity;
      capacity[current_node][next_node] += path_capacity;
      current_node = next_node;
    }
  }
  return total_flow;
}

int main() {
  ifstream fin("ditch.in");
  ofstream fout("ditch.out");

  fin >> n >> m;

  for (int i = 0; i < n; i++) {
    int x, y, z;
    fin >> x >> y >> z;
    capacity[x][y] += z;  // combine multiple ditches
  }

  fout << solve(1, m) << "\n";

  return 0;
}