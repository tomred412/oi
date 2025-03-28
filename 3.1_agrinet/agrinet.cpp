/*
ID: dermotl1
LANG: C++
PROG: agrinet
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int n;
int adj[100][100];

int solve() {
  vector<int> distance(n, 100001);
  vector<int> intree(n, false);
  vector<int> source(n, -1);
  distance[0] = 0;
  intree[0] = true;
  int treesize = 1;  // # of farm
  int treecost = 0;  // total amount

  for (int j = 0; j < n; j++) {
    distance[j] = adj[0][j];
    source[j] = 0;
  }
  while (treesize < n) {
    int i = -1;
    for (int j = 0; j < n; j++) {
      if (!intree[j] && (i == -1 || distance[j] < distance[i])) {
        i = j;
      }
    }

    treesize++;
    treecost += distance[i];
    intree[i] = true;
    for (int j = 0; j < n; j++) {
      if (!intree[j] && adj[i][j] < distance[j]) {
        distance[j] = adj[i][j];
        source[j] = i;
      }
    }
  }
  return treecost;
}

int main() {
  ifstream fin("agrinet.in");
  ofstream fout("agrinet.out");

  fin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fin >> adj[i][j];
    }
  }
  fout << solve() << "\n";
  return 0;
}
