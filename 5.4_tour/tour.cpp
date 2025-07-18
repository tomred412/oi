/*
ID: dermotl1
LANG: C++
PROG: tour
*/

#include <algorithm>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, v;
map<string, int> city_to_int;
vector<string> cities;
vector<int> adj[101];
int answers[101][101];  // x is one airplane going into, y is another airplane
                        // going back
int answer = 1;

bool CheckForRoute(int x, int y) {
  for (auto it : adj[x]) {
    if (it == y) return true;
  }
  return false;
}

void Solve() {
  answers[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      for (int k = 0; k < j; ++k) {
        if (answers[i][k] != 0 && CheckForRoute(k, j)) {
          if (answers[i][j] < answers[i][k] + 1)
            answers[i][j] =
                answers[i][k] + 1;  // go from k to j, let's count it up?
        }
      }
      answers[j][i] = answers[i][j];
    }
    if (CheckForRoute(i, n - 1) && answer < answers[i][n - 1]) {
      answer = answers[i][n - 1];
    }
  }
}

int main() {
  ifstream fin("tour.in");
  ofstream fout("tour.out");

  fin >> n >> v;

  for (int i = 0; i < n; ++i) {
    string temp;
    fin >> temp;
    city_to_int[temp] = i;
    cities.push_back(temp);
  }

  for (int i = 0; i < v; ++i) {
    string temp1, temp2;
    fin >> temp1 >> temp2;

    int x = city_to_int[temp1];
    int y = city_to_int[temp2];

    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  Solve();
  fout << answer << "\n";

  return 0;
}
