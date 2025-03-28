/*
ID: dermotl1
LANG: C++
PROG: inflate
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("inflate.in");
  ofstream fout("inflate.out");

  int n, m;
  fin >> m >> n;

  vector<int> array(m + 1, 0);

  for (int i = 0; i < n; i++) {
    int points, minutes;
    fin >> points >> minutes;

    for (int j = minutes; j <= m; j++) {
      array[j] = max(array[j], array[j - minutes] + points);
    }
  }
  fout << array[m] << "\n";
  return 0;
}
