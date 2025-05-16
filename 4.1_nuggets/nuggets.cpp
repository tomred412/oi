/*
ID: dermotl1
LANG: C++
PROG: nuggets
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int gcd(int a, int b) {
  while (b != 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

bool can_make_nugget[65536];

int main() {
  ifstream fin("nuggets.in");
  ofstream fout("nuggets.out");

  int n = 0;
  int pack[10];
  int max_pack = 0;

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> pack[i];
    if (pack[i] > max_pack) max_pack = pack[i];
  }

  int gcds = pack[0];
  for (int i = 1; i < n; ++i) {
    gcds = gcd(gcds, pack[i]);
  }
  if (gcds != 1) {
    fout << "0\n";
    return 0;
  }

  can_make_nugget[0] = true;

  for (int i = 1; i < 65536; ++i) {  // fill the array
    for (int j = 0; j < n; ++j) {
      if (i >= pack[j] && can_make_nugget[i - pack[j]]) {
        can_make_nugget[i] = true;
        break;
      }
    }
  }

  int run = 0;
  int answer = 0;
  for (int i = 1; i < 65536; ++i) {  // find the answer by finding the end point
    if (can_make_nugget[i]) {
      run++;
      if (run >= max_pack)
        break;  // since these consecutive numbers can just repeat
    } else {
      run = 0;     // reset
      answer = i;  // latest number
    }
  }
  fout << answer << "\n";
  return 0;
}