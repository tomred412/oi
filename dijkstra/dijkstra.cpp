#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct adjacency {
  int near;
  int cost;
};
int infinity = numeric_limits<int>::max();

vector<vector<adjacency> > adj;
int v;

int minimum(int dist[100],
            bool visited[100]) {  // dist for not permamnent shortest distances
  int min_value = infinity;
  int min_location = -1;
  for (int i = 0; i < v; ++i) {
    if (!visited[i] && dist[i] <= min_value) {
      min_value = dist[i];
      min_location = i;
    }
  }
  return min_location;
}

int solve(int start, int finish) {  // distance from start to finish
  int dist[100];
  bool visited[100];

  for (int i = 0; i < v; ++i) {
    dist[i] = infinity;
    visited[i] = false;
  }

  dist[start] = 0;

  for (int i = 0; i < v; ++i) {
    int a = minimum(dist, visited);
    if (a == -1) break;

    visited[a] = true;
    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i].near;
      int weight = adj[a][i].cost;
      if (!visited[b] && dist[a] != infinity && dist[a] + weight < dist[b]) {
        dist[b] = dist[a] + weight;
      }
    }
  }
  return dist[finish];
}

int main() {
  cout << "Please input number of verticies."
          "\n";

  cin >> v;
  adj.resize(v);

  cout << "Please enter adjacency list (enter a value, space, value, meaning "
          "those are connected, then the cost: ex. 2 3 8, from 2 to 3 or 3 to "
          "2 is distance 8). When you are done entering enter -1. \n";

  int x, y, cost;

  while (cin >> x && x != -1) {
    cin >> y >> cost;
    adjacency temp;
    temp.near = y;
    temp.cost = cost;
    adj[x].push_back(temp);
    temp.near = x;
    adj[y].push_back(temp);
  }

  int start;
  cout << "Please enter the starting point.\n";
  cin >> start;

  for (int i = 0; i < v; i++) {
    int shortest = solve(start, i);
    if (shortest == infinity) {
      cout << "There isn't a path from " << start << " to " << i << ".\n";
    } else {
      cout << "The shortest path to " << i << " is " << shortest << ".\n";
    }
  }
  return 0;
}
