/*
ID: dermotl1
LANG: C++
PROG: barn1
*/

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

bool comp(int a, int b) { return a > b; }

int main() {
  ifstream fin("barn1.in");
  ofstream fout("barn1.out");

  int M = 0;  // maximum number of boards that can be purchased
  int S = 0;  // total number of stalls
  int C = 0;  // number of cows in the stalls

  fin >> M >> S >> C;

  // the stall numbers
  int stalls[200];

  for (int i = 0; i < C; i++) {
    fin >> stalls[i];
  }

  // make sure it's in order
  sort(stalls, stalls + C);

  // the gap lengths between stalls (the amount of empty stalls, so -1 for that:
  // 3 and 4 doesn't count, but it's 1, so -1)
  int gaps[199];
  for (int i = 0; i < C - 1; i++) {
    gaps[i] = stalls[i + 1] - stalls[i] - 1;
  }

  sort(gaps, gaps + (C - 1), comp);

  // length of the stalls
  int total = stalls[C - 1] - stalls[0] + 1;

  for (int i = 0; i < M - 1 && i < C - 1; i++) {
    total -= gaps[i];
  }

  fout << total << "\n";

  return 0;
}
