/*
ID: dermotl1
LANG: C++
PROG: subset
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n;
int j;
long long tally[800];

int main() {
  ofstream fout("subset.out");
  ifstream fin("subset.in");

  fin >> n;

  j = n * (n + 1) / 2;
  if (j % 2 != 0) {
    fout << "0\n";
    return 0;
  }

  tally[0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int p = j / 2; p >= i; p--) {
      tally[p] = tally[p - i] + tally[p];
    }
  }

  fout << tally[j / 2] / 2 << "\n";

  return 0;
}
