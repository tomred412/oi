/*
ID: dermotl1
LANG: C++
PROG: comehome
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct adjacency {
  int near;
  int cost;
};
int infinity = numeric_limits<int>::max();

vector<vector<adjacency> > adj;
int v = 52;

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

  priority_queue<pair<int, int>, vector<pair<int, int> >,
                 greater<pair<int, int> > >
      heap;
  heap.push(make_pair(0, start));

  while (!heap.empty()) {
    pair<int, int> top = heap.top();
    heap.pop();

    int a = top.second;
    if (visited[a]) continue;
    visited[a] = true;

    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i].near;
      int weight = adj[a][i].cost;
      if (!visited[b] && dist[a] != infinity && dist[a] + weight < dist[b]) {
        dist[b] = dist[a] + weight;
        heap.push(make_pair(dist[b], b));
      }
    }
  }
  return dist[finish];
}

int convert(char a) {
  if ('a' <= a && a <= 'z')
    return a - 'a';  // lowercase = 0-25, uppercase = 26-51
  else
    return a - 'A' + 26;
}

int main() {
  ifstream fin("comehome.in");
  ofstream fout("comehome.out");

  int p;
  fin >> p;

  adj.resize(52);

  for (int i = 0; i < p; ++i) {
    char a, b;
    int cost;
    fin >> a >> b >> cost;

    int x = convert(a);
    int y = convert(b);

    adjacency temp;
    temp.near = y;
    temp.cost = cost;
    adj[x].push_back(temp);
    temp.near = x;
    adj[y].push_back(temp);
  }
  int min_dist = infinity;
  int answer;

  for (int i = 26; i < 52; ++i) {
    if (i == convert('Z')) continue;
    int a = solve(i, (convert('Z')));
    if (a < min_dist) {
      min_dist = a;
      answer = i;
    }
  }
  char result = 'A' + (answer - 26);
  fout << result << " " << min_dist << "\n";
}
