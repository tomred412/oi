/*
ID: dermotl1
LANG: C++
PROG: fact4
*/

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int main() {
  ifstream fin("fact4.in");
  ofstream fout("fact4.out");

  int n;
  fin >> n;

  int final = 1;

  for (int i = 2; i <= n; i++) {
    final = final * i;

    while (final % 10 == 0) {
      final = final / 10;
    }

    final = final % 10000;
  }
  fout << final % 10 << "\n";
}
