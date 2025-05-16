/*
ID: dermotl1
LANG: C++
PROG: fence6
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int n;
int lengths[101];
int infinity = numeric_limits<int>::max();
int segment_1_ids[101][8];
int segment_1_count[101];  // since each fence has 2 endpoints
int segment_2_ids[101][8];
int segment_2_count[101];

int fence_id[101][2];  // give each fence's endpoints another id
int id_counter = 0;
int graph[201][201];
bool used_edges[201][201];  // used edges
bool visited[201];          // used nodes

int min_loop = infinity;
int leader[201];

int find(int x) {
  if (leader[x] != x) leader[x] = find(leader[x]);
  return leader[x];
}

void merge(int x, int y) {
  int new_x = find(x);
  int new_y = find(y);
  if (new_x != new_y) leader[new_x] = new_y;
}

void dfs(int start, int current, int length,
         int steps) {  // find loops to find perimeters
  if (steps >= 2 && current == start) {
    if (length < min_loop) min_loop = length;
    return;
  }
  if (length >= min_loop) return;

  visited[current] = true;

  for (int i = 0; i < id_counter; ++i) {
    if (graph[current][i] > 0 &&
        used_edges[current][i] ==
            false) {  // if there exists one at all, and hasnt already been used

      used_edges[current][i] = true;
      used_edges[i][current] = true;

      dfs(start, i, length + graph[current][i], steps + 1);

      used_edges[current][i] = false;
      used_edges[i][current] = false;
    }
  }
}

int main() {
  ifstream fin("fence6.in");
  ofstream fout("fence6.out");

  fin >> n;

  for (int i = 0; i < n; ++i) {
    int s, length, n1, n2;
    fin >> s >> length >> n1 >> n2;
    lengths[s] = length;
    segment_1_count[s] = n1;
    segment_2_count[s] = n2;
    for (int j = 0; j < n1; ++j) {
      fin >> segment_1_ids[s][j];
    }
    for (int j = 0; j < n2; ++j) {
      fin >> segment_2_ids[s][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    fence_id[i][0] = id_counter;
    id_counter++;
    fence_id[i][1] = id_counter;
    id_counter++;
  }

  for (int i = 0; i < 201; ++i) {
    leader[i] = i;
  }

  for (int i = 1; i <= n;
       ++i) {  // must build the graph, with nodes being fence endpoints
    for (int j = 0; j < segment_1_count[i]; ++j) {
      int m = segment_1_ids[i][j];  // actual fence id
      bool found = false;
      for (int k = 0; k < segment_1_count[m]; ++k) {
        if (segment_1_ids[m][k] == i) {
          merge(fence_id[i][0], fence_id[m][0]);
          found = true;
          break;
        }
      }
      if (found == false) {
        for (int k = 0; k < segment_2_count[m]; ++k) {
          if (segment_2_ids[m][k] == i) {
            merge(fence_id[i][0], fence_id[m][1]);
            found = true;
            break;
          }
        }
      }
    }
    for (int j = 0; j < segment_2_count[i]; ++j) {
      int m = segment_2_ids[i][j];  // actual fence id
      bool found = false;
      for (int k = 0; k < segment_1_count[m]; ++k) {
        if (segment_1_ids[m][k] == i) {
          merge(fence_id[i][1], fence_id[m][0]);
          found = true;
          break;
        }
      }
      if (!found) {
        for (int k = 0; k < segment_2_count[m]; ++k) {
          if (segment_2_ids[m][k] == i) {
            merge(fence_id[i][1], fence_id[m][1]);
            found = true;
            break;
          }
        }
      }
    }
  }

  for (int i = 0; i <= n; ++i) {
    int a = find(fence_id[i][0]);
    int b = find(fence_id[i][1]);
    if (a != b) {
      graph[a][b] = lengths[i];
      graph[b][a] = lengths[i];
    }
  }

  for (int i = 1; i < 201; ++i) {
    for (int j = 0; j < 201; ++j) {
      for (int r = 0; r < 201; ++r) {
        used_edges[j][r] = false;
      }
    }
    dfs(i, i, 0, 0);
  }

  fout << min_loop << "\n";

  return 0;
}