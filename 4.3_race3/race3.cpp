/*
ID: dermotl1
LANG: C++
PROG: race3
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

vector<vector<int> > adj(50);
int counts;

void dfs(int start, vector<bool> &available, int avoid = -1) {
  if (start == avoid) return;
  available[start] = true;
  for (auto it : adj[start]) {
    if (!available[it]) dfs(it, available, avoid);
  }
}

int main() {
  ifstream fin("race3.in");
  ofstream fout("race3.out");

  while (true) {
    int n;
    fin >> n;
    if (n == -1) break;
    while (n != -2) {
      adj[counts].push_back(n);
      fin >> n;
    }
    counts++;
  }
  int finish = counts - 1;

  vector<int> unavoidable;

  for (int i = 1; i < finish; ++i) {
    vector<bool> available(counts, false);
    dfs(0, available, i);
    if (!available[finish]) unavoidable.push_back(i);
  }
  vector<int> split;

  for (auto it : unavoidable) {
    vector<bool> available_start(counts, false);
    dfs(0, available_start, it);

    vector<bool> available_other(counts, false);
    dfs(it, available_other, -1);

    bool overlap = false;
    for (int i = 0; i < counts; ++i) {
      if (i != it && available_start[i] && available_other[i]) {
        overlap = true;
        break;
      }
    }
    if (!overlap) split.push_back(it);
  }
  fout << unavoidable.size();
  for (auto it : unavoidable) {
    fout << " " << it;
  }
  fout << "\n";

  fout << split.size();
  for (auto it : split) {
    fout << " " << it;
  }
  fout << "\n";

  return 0;
}