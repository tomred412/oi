/*
ID: dermotl1
LANG: C++
PROG: telecow
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int capacity[202][202];
int max_flow[202];
bool visited[202];
int previous_node[202];
int m_after;

int solve(int source, int sink) {
  int total_flow = 0;
  while (true) {
    memset(max_flow, 0, sizeof(max_flow));
    memset(visited, false, sizeof(visited));
    memset(previous_node, -1, sizeof(previous_node));

    queue<int> path;
    path.push(source);
    visited[source] = true;

    max_flow[source] = numeric_limits<int>::max();

    while (!path.empty()) {
      int current = path.front();  // this one is different from reconstruction
      path.pop();
      int max_flows = 0;
      int max_loc = -1;

      for (int i = 1; i <= m_after; ++i) {
        if (!visited[i] && capacity[current][i] > 0) {
          visited[i] = true;
          previous_node[i] = current;
          path.push(i);
        }
      }
    }
    if (!visited[sink]) break;  // if there is no flow to sink

    int path_capacity = numeric_limits<int>::max();
    int current_node = sink;

    while (current_node != source) {
      int next_node = previous_node[current_node];
      path_capacity = min(path_capacity, capacity[next_node][current_node]);
      current_node = next_node;
    }
    current_node = sink;
    while (current_node != source) {
      int next_node = previous_node[current_node];
      capacity[next_node][current_node] -= path_capacity;
      capacity[current_node][next_node] += path_capacity;
      current_node = next_node;
    }
    total_flow += path_capacity;
  }
  return total_flow;
}

int main() {
  ifstream fin("telecow.in");
  ofstream fout("telecow.out");

  int n, m, c1, c2;
  fin >> n >> m >> c1 >> c2;
  m_after = n * 2;  //"m" for the nodes

  for (int i = 1; i <= n; ++i) {  // split each node into 2, so that they form a
                                  // path. to get to c2, it needs to cross this
                                  // path. so, able to use solve edmons karp
    int in_node = 2 * i - 1;
    int out_node = 2 * i;
    if (i == c1 || i == c2) {
      capacity[in_node][out_node] = numeric_limits<int>::max();
    } else {
      capacity[in_node][out_node] = 1;
    }
  }

  for (int i = 0; i < m; ++i) {  // add real ones
    int x, y;
    fin >> x >> y;

    int in_x = 2 * x - 1;
    int out_x = 2 * x;
    int in_y = 2 * y - 1;
    int out_y = 2 * y;

    capacity[out_x][in_y] = numeric_limits<int>::max();
    capacity[out_y][in_x] = numeric_limits<int>::max();
  }

  int source = 2 * c1;    // out
  int sink = 2 * c2 - 1;  // in

  int original[202][202];
  memcpy(original, capacity, sizeof(capacity));

  int go_down_answer = solve(source, sink);  // first answer
  // to find the second answer, remove each one

  vector<int> answer;
  int current[202][202];
  memcpy(current, original, sizeof(original));

  for (int i = 1; i <= n; ++i) {
    if (i == c1 || i == c2) continue;
    if (answer.size() == go_down_answer) break;

    int in_i = 2 * i - 1;
    int out_i = 2 * i;

    int temp[202][202];
    memcpy(temp, current, sizeof(current));
    temp[in_i][out_i] = 0;  // test it

    memcpy(capacity, temp, sizeof(temp));
    int test = solve(source, sink);

    if (test == go_down_answer - answer.size() - 1) {
      answer.push_back(i);
      memcpy(current, temp, sizeof(temp));
    }
  }

  fout << go_down_answer << "\n";

  for (int i = 0; i < answer.size(); ++i) {
    if (i > 0) fout << " ";
    fout << answer[i];
  }
  fout << "\n";

  return 0;
}