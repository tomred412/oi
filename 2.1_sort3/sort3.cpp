/*
ID: dermotl1
LANG: C++
PROG: sort3
*/

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

int main() {
  ofstream fout("sort3.out");
  ifstream fin("sort3.in");

  int n;
  fin >> n;

  vector<int> original(n);
  vector<int> sorted(n);

  for (int i = 0; i < n; i++) {
    fin >> original[i];
    sorted[i] = original[i];
  }

  sort(sorted.begin(), sorted.end());

  int num = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      if (original[i] != sorted[i] && original[j] != sorted[j] &&
          original[i] == sorted[j] && original[j] == sorted[i]) {
        swap(original[i], original[j]);
        num++;
        break;
      }
    }
  }

  int unsort = 0;
  for (int i = 0; i < n; i++) {
    if (original[i] != sorted[i]) unsort++;
  }

  num = (unsort / 3) * 2 + num;  // pairs

  fout << num << "\n";
  return 0;
}
