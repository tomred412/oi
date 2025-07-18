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
vector<int> adj[100];
bool visited[100];
int answer = 1;

void ReturnTrip(int current, int count) {
  if (current == 0) {  // we're finished with the entire trip
    if (count > answer) answer = count;
    return;
  }

  for (int i = 0; i < adj[current].size(); ++i) {
    int next = adj[current][i];

    if (next == 0) {
      ReturnTrip(0, count);
    } else if (next < current && !visited[next]) {  // go from east to west only

      visited[next] = true;
      ReturnTrip(next, count + 1);
      visited[next] = false;
    }
  }
}

void ToDestinationTrip(int current, int count) {
  if (current == n - 1) {
    ReturnTrip(current, count);  // we're at the end, we should return
    return;
  }

  for (int i = 0; i < adj[current].size(); ++i) {
    int next = adj[current][i];

    if (next > current && (!visited[next])) {
      visited[next] = true;
      ToDestinationTrip(next, count + 1);
      visited[next] = false;
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

  visited[0] = true;  // 0 is the start city, so its already visited
  ToDestinationTrip(0, 1);
  fout << answer << "\n";
  return 0;
}