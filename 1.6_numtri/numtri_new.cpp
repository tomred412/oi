/*
ID: dermotl1
LANG: C++
PROG: numtri
*/

#include <algorithm>
#include <fstream>

using namespace std;

int main() {
  ofstream fout("numtri.out");
  ifstream fin("numtri.in");

  int n;
  fin >> n;
  int array[1000];
  int temp[1000][1000];
  int p;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      fin >> temp[i][j];
    }
  }

  for (int j = 0; j < n; j++) {
    array[j] = temp[n - 1][j];
  }

  for (int i = n - 2; i >= 0; i--) {
    for (int j = 0; j <= i; j++) {
      array[j] = temp[i][j] + max(array[j], array[j + 1]);
    }
  }

  fout << array[0] << "\n";
}
