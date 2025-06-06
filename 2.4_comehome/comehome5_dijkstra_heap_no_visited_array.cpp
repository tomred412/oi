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
adjacency heap[10000];
int heap_size = 0;

vector<vector<adjacency> > adj;
int v = 52;

void push(adjacency value) {
  int pos = heap_size;
  ++heap_size;
  heap[pos] = value;

  while (pos > 0) {
    int parent = (pos - 1) / 2;
    if (heap[parent].cost <= heap[pos].cost) break;
    swap(heap[parent], heap[pos]);
    pos = parent;
  }
}

adjacency pop() {
  adjacency top = heap[0];
  --heap_size;
  heap[0] = heap[heap_size];

  int pos = 0;
  while (true) {
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;
    int smallest = pos;

    if (left < heap_size && heap[left].cost < heap[smallest].cost)
      smallest = left;
    if (right < heap_size && heap[right].cost < heap[smallest].cost)
      smallest = right;

    if (smallest == pos) break;
    swap(heap[pos], heap[smallest]);
    pos = smallest;
  }
  return top;
}

int solve(int start, int finish) {  // distance from start to finish
  heap_size = 0;
  int dist[100];

  for (int i = 0; i < v; ++i) {
    dist[i] = infinity;
  }

  dist[start] = 0;

  adjacency temp;
  temp.cost = 0;
  temp.near = start;
  push(temp);

  while (heap_size > 0) {
    adjacency top = pop();

    int a = top.near;
    int d = top.cost;

    if (d != dist[a]) continue;

    for (int i = 0; i < adj[a].size(); ++i) {
      int b = adj[a][i].near;
      int weight = adj[a][i].cost;
      if (dist[a] != infinity && dist[a] + weight < dist[b]) {
        dist[b] = dist[a] + weight;
        adjacency temp1;
        temp1.near = b;
        temp1.cost = dist[b];
        push(temp1);
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
