// read graph
// find next closest node to 0
// repeat until there are no more nodes to be added, for all values

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > array(n + 1);  // adjacanecy
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    array[a].push_back(b);
    array[b].push_back(a);
  }

  vector<int> path(n + 1, -1);  // set it to -1, where we came from
  queue<int> process;           // queue to process everything

  process.push(1);
  path[1] = 0;

  while (process.empty() == false) {  // one by one
    int a = process.front();
    process.pop();
    for (int i = 0; i < array[a].size(); i++) {  // everything from a
      int temp = array[a][i];
      if (path[temp] == -1) {
        path[temp] = a;
        process.push(temp);
      }
    }
  }
  if (path[n] == -1) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  vector<int> repath;
  for (int i = n; i != 0; i = path[i]) {
    repath.push_back(i);
  }
  reverse(repath.begin(), repath.end());

  cout << repath.size() << "\n";
  for (int i = 0; i < repath.size(); i++) {
    cout << repath[i] << " ";
  }
  cout << "\n";

  return 0;
}
